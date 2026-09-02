#!/bin/bash
#
# NAME:
#         port_commits.sh - Port a range of commits from parent ACPICA
#                          git repository into locally cloned Linux kernel
#                          tree
#
# SYNOPSIS:
#         port_commits.sh <-d kernel_dir> <-b branch_name> [-c policy]
#                         [-l log_file] [-a] [-f] [-r] <A...B>
#
# DESCRIPTION:
#         Processes a specified range of ACPICA commits and updates the
#         respective files in the given local Linux kernel tree, creating a
#         new branch for the ported updates. The script automatically omits
#         merge commits and changes that are not applicable to the Linux
#         kernel. Optional mode -a enables porting of files that do not yet
#         exist in the kernel tree, placing them according to their original
#         directory structure in the ACPICA repository, with the destination
#         directory being dependent on the path inside ACPICA tree.
#
#         Commits that already appear to be ported are skipped: a kernel
#         commit whose subject mentions "ACPICA" and whose message references
#         the short SHA of the ACPICA commit marks it as already ported.
#
#         Because that detection also covers the branch being built, a run can
#         be resumed: with -r an already existing branch is checked out and
#         added to instead of being rejected, so re-running the same range
#         after resolving conflicts ports only what is still missing. On abort,
#         a branch that existed beforehand is rewound to where the run found
#         it, never deleted.
#
#         Each commit message is rewritten for the kernel: the "ACPICA: "
#         subject prefix, a "Link:" to the original ACPICA commit and a
#         "Signed-off-by:" trailer are added automatically.
#
#         When a converted change does not apply cleanly, the action taken is
#         determined by the conflict policy (-c):
#           ask    - the default; ask on the terminal, offering the same
#                    choices as an interactive git rebase:
#                      continue - force-apply the change, then pause to let
#                                 the rejected hunks be resolved manually
#                                 (e.g. in another shell), then resume;
#                      skip     - discard this commit's partial changes and
#                                 move on;
#                      abort    - restore the kernel repo to its original
#                                 state (return to the previous branch and
#                                 delete the created branch);
#                      pause    - stop the run here (as Ctrl-C would) so this
#                                 one change can be ported by hand, keeping
#                                 the branch and every commit already ported;
#                                 resume the rest later with -r.
#           abort  - non-interactive; behave as the "abort" answer above.
#           force  - non-interactive; behave as the "continue" answer above,
#                    committing the partial change. Rejected hunks are
#                    reported on stderr and in the log before being removed.
#         "skip" and "pause" are deliberately not available as -c values:
#         silently dropping commits, or stopping half-way, are decisions for a
#         human at the prompt, not defaults for an unattended run.
#
#         All diagnostics (Error:/Warning:) go to stderr only, so stdout
#         carries progress and the final summary. A transcript of the run,
#         including git and patch output, is appended to the log file (-l).
#
#         No patch artifacts (*.rej, *.orig) are left behind: every reject
#         created by the script is reported and then removed, including on
#         abort, failure or interruption.
#
#         Parameters:
#         -d      Path to Linux kernel tree, to port into
#         -b      New branch name to create in kernel tree
#         A...B   Range of commits from ACPICA to port into kernel tree.
#
#         Options:
#         -c    Conflict policy: ask (default), abort or force
#         -l    Log file (default: ${TMPDIR}/port_commits-<branch>.log)
#         -a    Whether to add new files that don't yet exist in the kernel
#         -f    Proceed even if the kernel tree has uncommitted changes
#         -r    Resume: continue onto <branch_name> if it already exists
#         -h    This help message
#
# EXIT STATUS:
#         0     All commits in the range were handled cleanly
#         1     Usage error
#         2     Environment or precondition failure (nothing was modified)
#         3     Finished, but at least one commit was skipped, committed with
#               rejected hunks, or failed to commit - needs human attention
#         4     Aborted on conflict; the kernel repo was restored
#         5     Paused at a conflict ('p' answer); the branch and the commits
#               already ported were kept, so the run can be resumed with -r
#         130   Interrupted (SIGINT); 143 for SIGTERM
#

set -o pipefail

KERNEL_DIR=""
BRANCH_NAME=""
ADD_NEW=0
ALLOW_DIRTY=0
RESUME=0
CONFLICT_POLICY="ask"
LOG_FILE=""
SERIE_CNTR=0
SKIPPED_CNTR=0
PARTIAL_CNTR=0
FAILED_CNTR=0
PREFIX="ACPICA"
TOOL_DIR=$(dirname "$(realpath "$0")")
INVOKE_DIR="${PWD}"
# BRANCH_EXISTED: the target branch was there before this run, so an abort must
#                 rewind it rather than delete it.
# BRANCH_CREATED: this run created the branch; an abort may delete it.
# KERNEL_TOUCHED: the kernel repo has been switched/modified, so any failure has
#                 to unwind before exiting.
BRANCH_EXISTED=0
BRANCH_CREATED=0
KERNEL_TOUCHED=0
RESUME_BASE=""
TTY_OK=0
LAST_PORTED=""
declare -a REJECT_FILES=()

# Exit codes
EXIT_OK=0
EXIT_USAGE=1
EXIT_ENV=2
EXIT_INCOMPLETE=3
EXIT_ABORTED=4
EXIT_PAUSED=5

help() {
  cat <<EOF
help:
  $0 <-d kernel_dir> <-b branch_name> [-c policy] [-l log_file] [-a] [-f] [-r] <A...B>

Parameters:
  -d      Path to Linux kernel tree, to port into
  -b      New branch name to create in kernel tree
   A...B  Range of commits from ACPICA to port into kernel tree

Options:
  -c    Conflict policy: ask (default, interactive), abort or force
  -l    Log file (default: \${TMPDIR}/port_commits-<branch>.log)
  -a    Whether to add new files that don't yet exist in the kernel
  -f    Proceed even if the kernel tree has uncommitted changes
  -r    Resume: continue onto <branch_name> if it already exists
  -h    This help message

Exit status: 0 clean, 1 usage, 2 environment, 3 needs attention, 4 aborted,
             5 paused (resume with -r)
EOF
}

log() {
  [[ -n "${LOG_FILE}" ]] && printf '%s\n' "$*" >> "${LOG_FILE}" 2>/dev/null
  return 0
}

info() {
  printf '%s\n' "$*"
  log "$*"
}

warn() {
  printf 'Warning: %s\n' "$*" >&2
  log "Warning: $*"
}

err() {
  printf 'Error: %s\n' "$*" >&2
  log "Error: $*"
}

declare -A DEST_DIRS=(
  ["source/include"]="include/acpi"
  ["source/components/debugger"]="drivers/acpi/acpica"
  ["source/components/disassembler"]="drivers/acpi/acpica"
  ["source/components/dispatcher"]="drivers/acpi/acpica"
  ["source/components/events"]="drivers/acpi/acpica"
  ["source/components/executer"]="drivers/acpi/acpica"
  ["source/components/hardware"]="drivers/acpi/acpica"
  ["source/components/namespace"]="drivers/acpi/acpica"
  ["source/components/parser"]="drivers/acpi/acpica"
  ["source/components/resources"]="drivers/acpi/acpica"
  ["source/components/tables"]="drivers/acpi/acpica"
  ["source/components/utilities"]="drivers/acpi/acpica"
  ["source/os_specific/service_layers"]="tools/power/acpi/os_specific/service_layers"
  ["source/common"]="tools/power/acpi/common"
  ["source/tools/acpidump"]="tools/power/acpi/tools/acpidump"
)

while getopts ":d:b:c:l:afrh" opt; do
  case ${opt} in
    d ) KERNEL_DIR="$OPTARG" ;;
    b ) BRANCH_NAME="$OPTARG" ;;
    c ) CONFLICT_POLICY="$OPTARG" ;;
    l ) LOG_FILE="$OPTARG" ;;
    a ) ADD_NEW=1 ;;
    f ) ALLOW_DIRTY=1 ;;
    r ) RESUME=1 ;;
    h ) help; exit ${EXIT_OK} ;;
    \? ) err "Invalid option: -$OPTARG"; help >&2; exit ${EXIT_USAGE} ;;
    : ) err "Option -$OPTARG requires an argument."; help >&2; exit ${EXIT_USAGE} ;;
  esac
done

# Remove parsed options from "$@"
shift $((OPTIND - 1))

if [ $# -lt 1 ]; then
  err "Not specified a range of commits to process."
  echo "Usage: $0 [options] <A...B>" >&2
  exit ${EXIT_USAGE}
fi

RANGE="$1"

if ! [[ $RANGE =~ ^[^[:space:]]+\.\.[^[:space:]]+$ ]]; then
  err "Invalid range of commits to process: ${RANGE}"
  echo "Usage: $0 [options] <A...B>" >&2
  exit ${EXIT_USAGE}
fi

if [[ -z "${KERNEL_DIR}" || -z "${BRANCH_NAME}" ]]; then
  err "values for parameters -d, -b are required."
  help >&2
  exit ${EXIT_USAGE}
fi

case "${CONFLICT_POLICY}" in
  ask|abort|force )
    ;;
  skip )
    err "-c skip is not supported: 'skip' is only available interactively," \
        "as the 's' answer at the conflict prompt."
    exit ${EXIT_USAGE} ;;
  pause )
    err "-c pause is not supported: 'pause' is only available interactively," \
        "as the 'p' answer at the conflict prompt."
    exit ${EXIT_USAGE} ;;
  * )
    err "Invalid conflict policy '${CONFLICT_POLICY}' (expected ask, abort or force)."
    exit ${EXIT_USAGE} ;;
esac

if [[ -z "${LOG_FILE}" ]]; then
  LOG_FILE="${TMPDIR:-/tmp}/port_commits-${BRANCH_NAME}.log"
fi

# Resolve the log path against the invocation directory, then make sure it is
# writable before anything else depends on it.
if [[ "${LOG_FILE}" != /* ]]; then
  LOG_FILE="${INVOKE_DIR}/${LOG_FILE}"
fi
if ! touch "${LOG_FILE}" 2>/dev/null; then
  printf 'Error: cannot write log file: %s\n' "${LOG_FILE}" >&2
  exit ${EXIT_ENV}
fi

log "=== port_commits.sh $(date -u '+%Y-%m-%dT%H:%M:%SZ') ==="
log "args: -d '${KERNEL_DIR}' -b '${BRANCH_NAME}' -c '${CONFLICT_POLICY}' -a ${ADD_NEW} -f ${ALLOW_DIRTY} -r ${RESUME} range '${RANGE}'"
info "Logging to ${LOG_FILE}"

PARENT_DIR="$(git rev-parse --show-toplevel 2>/dev/null || true)"
if [[ -z "${PARENT_DIR}" ]]; then
  err "Not in the ACPICA repo."
  exit ${EXIT_ENV}
fi

ACPISRC="${PARENT_DIR}/generate/unix/bin/acpisrc"
if [[ ! -x "${ACPISRC}" ]]; then
  err "acpisrc not found: ${ACPISRC}"
  exit ${EXIT_ENV}
fi

if ! command -v clang-format >/dev/null 2>&1; then
  err "clang-format not found in PATH."
  exit ${EXIT_ENV}
fi

# --- Kernel tree preconditions -------------------------------------------
# Checked before anything is cloned or modified, so a failure here leaves both
# repositories untouched.

if [[ ! -d "${KERNEL_DIR}" ]]; then
  err "kernel tree not found: ${KERNEL_DIR}"
  exit ${EXIT_ENV}
fi

KERNEL_DIR="$(realpath "${KERNEL_DIR}")"

if ! git -C "${KERNEL_DIR}" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  err "not a git working tree: ${KERNEL_DIR}"
  exit ${EXIT_ENV}
fi

if git -C "${KERNEL_DIR}" show-ref --verify --quiet "refs/heads/${BRANCH_NAME}"; then
  if [[ "${RESUME}" -eq 0 ]]; then
    err "branch already exists ${BRANCH_NAME}; pass -r to continue porting onto it."
    exit ${EXIT_ENV}
  fi
  BRANCH_EXISTED=1
fi

# A dirty kernel tree is rejected up front rather than in the middle of the
# porting loop, where bailing out would leave a half-built branch behind.
if [[ "${ALLOW_DIRTY}" -eq 0 ]]; then
  KERNEL_STATUS="$(git -C "${KERNEL_DIR}" status --porcelain --untracked-files=no)"
  if [[ -n "${KERNEL_STATUS}" ]]; then
    err "kernel tree has uncommitted changes; commit or stash them first (or pass -f):"
    printf '%s\n' "${KERNEL_STATUS}" >&2
    log "${KERNEL_STATUS}"
    exit ${EXIT_ENV}
  fi
fi

# Signed-off-by is taken from the kernel repo, which is where the commits land.
SOB_NAME="$(git -C "${KERNEL_DIR}" config user.name || true)"
SOB_EMAIL="$(git -C "${KERNEL_DIR}" config user.email || true)"
if [[ -z "${SOB_NAME}" || -z "${SOB_EMAIL}" ]]; then
  err "user.name/user.email are not set in ${KERNEL_DIR}; cannot build Signed-off-by."
  exit ${EXIT_ENV}
fi
SIGNED_OFF_BY="Signed-off-by: ${SOB_NAME} <${SOB_EMAIL}>"

# --- Conflict prompt -----------------------------------------------------
# Open the terminal once, for the whole run. The probe runs in a subshell on
# purpose: 'exec' is a special builtin, so a failing redirection here would
# terminate a non-interactive shell instead of letting us report the problem.
if ( exec 3<>/dev/tty ) 2>/dev/null; then
  exec 3<>/dev/tty
  TTY_OK=1
fi

if [[ "${CONFLICT_POLICY}" == "ask" && "${TTY_OK}" -eq 0 ]]; then
  err "no controlling terminal available for -c ask."
  err "Use -c abort or -c force for non-interactive runs."
  exit ${EXIT_ENV}
fi

# Decide what to do about a conflict. Echoes exactly one of:
#   continue | skip | abort | pause
# 'pause' is interactive-only, like 'skip': -c force and -c abort answer before
# the prompt is ever reached, so no unattended run can stop half-way.
# NOTE: stdout is captured by the caller, so all human-facing text must go to
# fd 3 (the terminal) or stderr - never to stdout.
ask_conflict() {
  local prompt="$1" ans

  case "${CONFLICT_POLICY}" in
    force ) echo continue; return ;;
    abort ) echo abort;    return ;;
  esac

  while true; do
    printf '%s\nChoose: [c]ontinue / [s]kip / [a]bort / [p]ause: ' "${prompt}" >&3
    if ! read -r -u 3 ans; then
      # EOF (Ctrl-D) or the terminal went away: fail safe instead of spinning
      # on a read that will never succeed.
      printf '\nNo answer available, aborting.\n' >&3
      echo abort
      return
    fi
    case "${ans}" in
      c|continue ) echo continue; return ;;
      s|skip )     echo skip;     return ;;
      a|abort )    echo abort;    return ;;
      p|pause )    echo pause;    return ;;
      * ) printf 'Please answer c, s, a or p.\n' >&3 ;;
    esac
  done
}

# --- Patch artifact bookkeeping ------------------------------------------
# Rejects are tracked by exact path, so cleanup never has to sweep the kernel
# tree and can never delete a *.rej/*.orig that the script did not create.
record_rejects() {
  local dir="$1" name="$2" f line
  for f in "${dir}/${name}.rej" "${dir}/${name}.orig"; do
    [[ -f "${f}" ]] || continue
    REJECT_FILES+=("${f}")
    [[ "${f}" == *.rej ]] || continue
    warn "rejected hunks left in ${f}:"
    while IFS= read -r line; do
      printf '  | %s\n' "${line}" >&2
      log "  | ${line}"
    done < "${f}"
  done
}

delete_rejects() {
  local f
  if [[ "${#REJECT_FILES[@]}" -gt 0 ]]; then
    for f in "${REJECT_FILES[@]}"; do
      rm -f "${f}" >/dev/null 2>&1 || true
    done
  fi
  REJECT_FILES=()
}

TMP_ACPICA="$(mktemp -d "${TMPDIR:-/tmp}/acpica_port_commits_XXXXXXXX")" || {
  err "cannot create temporary directory."
  exit ${EXIT_ENV}
}
# Scratch dir for per-file temporaries, kept inside the temporary ACPICA clone
# (created after the clone below, since the clone target must be empty).
TMP_WORK="${TMP_ACPICA}/.port_commits_tmp"

# From now on, if anything goes wrong, delete the temporary working directory,
# the temporary working files and any patch artifacts we created.
cleanup() {
  delete_rejects
  rm -rf "${TMP_ACPICA}" >/dev/null 2>&1 || true
}
trap cleanup EXIT

# Restore kernel repo in case of abort: back to the original branch, with the
# branch we created removed. A branch that existed before this run is rewound to
# where we found it instead - resuming must not destroy somebody else's work.
abort_port() {
  warn "aborting: restoring kernel repo to its state before porting."
  delete_rejects
  cd "${KERNEL_DIR}" || return 0
  git reset --hard "${RESUME_BASE:-HEAD}" >/dev/null 2>&1 || true
  git checkout -- . >/dev/null 2>&1 || true
  git checkout -q "${ORIG_BRANCH}" >/dev/null 2>&1 || true
  if [[ "${BRANCH_CREATED}" -eq 1 ]]; then
    git branch -D "${BRANCH_NAME}" >/dev/null 2>&1 || true
    BRANCH_CREATED=0
  elif [[ "${BRANCH_EXISTED}" -eq 1 ]]; then
    warn "kept pre-existing branch '${BRANCH_NAME}', rewound to ${RESUME_BASE:0:12}."
  fi
  KERNEL_TOUCHED=0
}

# Unwind an unexpected failure or interruption: drop the partially applied
# commit, but keep the branch and the commits that were ported successfully -
# unlike an explicit abort, this is not a request to throw work away.
unwind_incomplete() {
  delete_rejects
  cd "${KERNEL_DIR}" 2>/dev/null || return 0
  git reset --hard >/dev/null 2>&1 || true
  warn "kept branch '${BRANCH_NAME}' with ${SERIE_CNTR} commit(s) ported by this run; working tree reset."
  if [[ -n "${LAST_PORTED}" ]]; then
    warn "last ported ACPICA commit: ${LAST_PORTED}"
  fi
  warn "re-run the same range with -r to continue; already-ported commits are detected and skipped."
}

# The 'p' answer at a conflict prompt: stop here so the change can be ported by
# hand, then resumed. Deliberately the same unwind as Ctrl-C - keep the branch
# and every commit already ported, drop only the half-applied one - so the two
# ways of stopping leave the repo in exactly the same shape. Exits via the EXIT
# trap, which removes the temporary clone.
pause_port() {
  local what="$1"
  info "Paused at ${what}."
  if [[ "${KERNEL_TOUCHED}" -eq 1 ]]; then
    unwind_incomplete
  fi
  info "Port this change by hand, then resume with:"
  # -r is a flag and the range is the positional argument, so the hint has to be
  # spelled exactly the way the option parser expects it - it is meant to be
  # copied and pasted. The optional flags are echoed back only if they were used.
  local resume_cmd="$0 -d '${KERNEL_DIR}' -b '${BRANCH_NAME}' -c '${CONFLICT_POLICY}'"
  [[ "${ADD_NEW}" -eq 1 ]]     && resume_cmd+=" -a"
  [[ "${ALLOW_DIRTY}" -eq 1 ]] && resume_cmd+=" -f"
  resume_cmd+=" -l '${LOG_FILE}' -r ${RANGE}"
  info "  ${resume_cmd}"
  info "Give the manual commit an 'ACPICA:' subject and a"
  info "  Link: https://github.com/acpica/acpica/commit/<12-char sha>"
  info "line, so the resumed run detects it as already ported and skips it."
  exit ${EXIT_PAUSED}
}

# Fatal error handler: report, unwind if we already touched the kernel repo,
# then exit with the given status. Never exits without cleaning up.
die() {
  local code="$1"; shift
  err "$*"
  if [[ "${KERNEL_TOUCHED}" -eq 1 ]]; then
    unwind_incomplete
  fi
  exit "${code}"
}

on_signal() {
  local sig="$1"
  trap - EXIT INT TERM
  printf '\n' >&2
  err "interrupted by SIG${sig}."
  if [[ "${KERNEL_TOUCHED}" -eq 1 ]]; then
    unwind_incomplete
  fi
  cleanup
  case "${sig}" in
    INT )  exit 130 ;;
    TERM ) exit 143 ;;
  esac
}
trap 'on_signal INT' INT
trap 'on_signal TERM' TERM

# Discard any partial changes from the current commit and clean up leftovers.
skip_current_commit() {
  delete_rejects
  cd "${KERNEL_DIR}" || return 0
  git reset --hard >/dev/null 2>&1 || true
}

git clone "${PARENT_DIR}" "${TMP_ACPICA}" >> "${LOG_FILE}" 2>&1 || {
  err "cloning into temp acpica folder failed; see ${LOG_FILE}."
  exit ${EXIT_ENV}
}

mkdir -p "${TMP_WORK}" || {
  err "cannot create scratch directory ${TMP_WORK}."
  exit ${EXIT_ENV}
}

cd "${TMP_ACPICA}" || {
  err "cannot enter ${TMP_ACPICA}."
  exit ${EXIT_ENV}
}

if ! COMMITS_RAW="$(git rev-list --reverse --topo-order "${RANGE}" 2>&1)"; then
  err "could not get list of commits for range '${RANGE}':"
  printf '%s\n' "${COMMITS_RAW}" >&2
  log "${COMMITS_RAW}"
  exit ${EXIT_ENV}
fi

if [[ -z "${COMMITS_RAW}" ]]; then
  err "range '${RANGE}' contains no commits."
  exit ${EXIT_ENV}
fi

mapfile -t COMMITS <<< "${COMMITS_RAW}"

cd "${KERNEL_DIR}" || {
  err "cannot enter ${KERNEL_DIR}."
  exit ${EXIT_ENV}
}

# Remember the branch we started on, so an abort can restore it.
ORIG_BRANCH="$(git symbolic-ref --quiet --short HEAD 2>/dev/null || git rev-parse HEAD)"

if [[ "${BRANCH_EXISTED}" -eq 1 ]]; then
  # Resuming: add to the branch as it stands. Its own commits are picked up by
  # the already-ported index below, so the range can be replayed verbatim.
  if ! git checkout "${BRANCH_NAME}" >> "${LOG_FILE}" 2>&1; then
    err "could not check out existing branch ${BRANCH_NAME}; see ${LOG_FILE}."
    exit ${EXIT_ENV}
  fi
  KERNEL_TOUCHED=1
  RESUME_BASE="$(git rev-parse HEAD)"
  info "Resuming on existing branch '${BRANCH_NAME}' at ${RESUME_BASE:0:12}."
else
  if ! git checkout -b "${BRANCH_NAME}" >> "${LOG_FILE}" 2>&1; then
    err "could not create branch ${BRANCH_NAME} in ${KERNEL_DIR}; see ${LOG_FILE}."
    exit ${EXIT_ENV}
  fi
  BRANCH_CREATED=1
  KERNEL_TOUCHED=1
  RESUME_BASE="$(git rev-parse HEAD)"
fi

# Build the "already ported" lookup
info "Indexing already-ported ACPICA commits in ${KERNEL_DIR}..."
declare -A PORTED
while IFS=$'\t' read -r prefix khash; do
  [[ -n "${prefix}" ]] && PORTED["${prefix}"]="${khash}"
done < <(
  git -C "${KERNEL_DIR}" log --no-merges -z --format='%H%n%s%n%b' 2>/dev/null \
  | LC_ALL=C awk 'BEGIN { RS="\0" }
    {
      nl1 = index($0, "\n")
      khash = substr($0, 1, nl1 - 1)
      rest = substr($0, nl1 + 1)
      nl2 = index(rest, "\n")
      subject = (nl2 ? substr(rest, 1, nl2 - 1) : rest)
      if (index(subject, "ACPICA") == 0) next
      # Record the first 8 chars of every hex token in subject+body.
      # The class is spelled out rather than written as [0-9a-f]{8,40}: mawk
      # builds without interval-expression support match nothing at all there,
      # which silently emptied this index. Trailing * consumes the rest of the
      # token so RLENGTH advances past it.
      s = rest
      while (match(s, /[0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f]*/)) {
        print substr(s, RSTART, 8) "\t" khash
        s = substr(s, RSTART + RLENGTH)
      }
    }'
)

for CMT in "${COMMITS[@]}"; do
  ANYTHING_REJECTED=0
  ANYTHING_TO_ADD=0
  SKIP_COMMIT=0

  cd "${TMP_ACPICA}" || die ${EXIT_ENV} "cannot enter ${TMP_ACPICA}."
  info "Processing commit ${CMT} from ACPICA:"

  # Skip merge commits
  PARENT_COUNT="$(git rev-list --parents -n 1 "${CMT}" | awk '{print NF-1}')"
  if [[ "${PARENT_COUNT}" -ne 1 ]]; then
    info "Commit ${CMT}: is a merge commit (parents: ${PARENT_COUNT}), skipping."
    continue
  fi

  # Skip commits already ported: a kernel commit whose message contains the SHA of this ACPICA commit.
  CMT_SHORT="${CMT:0:8}"
  ALREADY_PORTED="${PORTED[${CMT_SHORT}]:-}"
  if [[ -n "${ALREADY_PORTED}" ]]; then
    info "Commit ${CMT}: already ported as kernel commit ${ALREADY_PORTED:0:12}, skipping."
    continue
  fi

  git checkout -- . >> "${LOG_FILE}" 2>&1
  git checkout -q "${CMT}" >> "${LOG_FILE}" 2>&1 \
    || die ${EXIT_ENV} "cannot check out ${CMT} in the temporary clone; see ${LOG_FILE}."

  # Automatically edit the commit message
  MESSAGE_SUBJECT="$(git log -1 $CMT --format='%s')"
  MESSAGE_OLD="$(git log -1 "$CMT" --format='%b' | tr -d '\r')"
  MESSAGE_TRAILERS="$(git log -1 $CMT --format='%B' | git interpret-trailers --parse)"
  MESSAGE_AUTHOR="$(git log -1 $CMT --format='%aN <%aE>')"

  if [[ -n "$PREFIX" && "$MESSAGE_SUBJECT" != "$PREFIX"* ]]; then
      MESSAGE_SUBJECT="${PREFIX}: ${MESSAGE_SUBJECT}"
  fi

  MESSAGE_NEW="${MESSAGE_SUBJECT}"$'\n\n'"$(printf '%s' "${MESSAGE_OLD/$MESSAGE_TRAILERS/}" | fmt -s)"

  # If the block doesn't end with new line, add two, so the "Link" doesn't stick to the body
  if [[ $MESSAGE_NEW != *$'\n' ]]; then
    MESSAGE_NEW+=$'\n\n'
  fi

  # Collect the SHAs referenced by 'Fixes:' trailers. Done in bash on purpose:
  # awk's regex support for {n,m} intervals is not portable (mawk builds without
  # it match nothing), and the 3-argument match() is a GNU extension.
  FIXED=()
  while IFS= read -r FIXES_LINE; do
    [[ "${FIXES_LINE}" == Fixes* ]] || continue
    if [[ "${FIXES_LINE}" =~ [0-9a-f]{7,40} ]]; then
      FIXED+=("${BASH_REMATCH[0]}")
    fi
  done <<< "$MESSAGE_TRAILERS"

  MESSAGE_NEW+="Link: https://github.com/acpica/acpica/commit/${CMT:0:12}"$'\n'
  MESSAGE_NEW+="${MESSAGE_TRAILERS}"

  for FIX in "${FIXED[@]}"; do
    if ! git -C "${KERNEL_DIR}" cat-file -e "${FIX}^{commit}" 2>/dev/null; then
      MESSAGE_NEW="$(
        sed -E "s/\b${FIX}\b/INVALID_COMMIT/g" <<< "$MESSAGE_NEW"
      )"
    fi
  done

  if ! grep -Fq "$SIGNED_OFF_BY" <<< "$MESSAGE_NEW"; then
      MESSAGE_NEW+=$'\n'"${SIGNED_OFF_BY}"
  fi
  # End of message processing

  # List of changed files
  mapfile -t CHANGED_FILES < <(git diff-tree --no-commit-id --name-status -r "${CMT}" \
    | awk '$1=="A" || $1=="M" {print $2}')

  if [[ "${#CHANGED_FILES[@]}" -eq 0 ]]; then
    info "Commit ${CMT}: No added/modified files, skipping."
    continue
  fi

  for FILE in "${CHANGED_FILES[@]}"; do
    SRC="${TMP_ACPICA}/${FILE}"
    SRC_DIR="$(dirname -- "$FILE")"
    FILE_NAME="$(basename -- "$FILE")"
    DEST=""

    for key in "${!DEST_DIRS[@]}"; do
      DST_REL="${DEST_DIRS[$key]}"
      KERNEL_COUNTERPART="${KERNEL_DIR}/${DST_REL}/${FILE_NAME}"
      if [[ -f "$KERNEL_COUNTERPART" ]]; then
        DEST="$KERNEL_COUNTERPART"
        break
      fi
    done

    if [[ -z "$DEST" ]]; then
      if [[ "${ADD_NEW}" != 0 && -n "${DEST_DIRS[$SRC_DIR]+_}" ]]; then
        DST_REL="${DEST_DIRS[$SRC_DIR]}"
        DEST="${KERNEL_DIR}/${DST_REL}/${FILE_NAME}"
      fi

      if [[ -z "$DEST" ]]; then
        continue
      fi
    fi

    # Compare against HEAD, not just the index: changes someone else staged in
    # the destination would otherwise slip through unnoticed.
    if ! git -C "$KERNEL_DIR" diff --quiet HEAD -- "$DEST"; then
      warn "destination has changes not made by this script: ${DEST}"
      case "$(ask_conflict "Unexpected local changes in ${DEST}.")" in
        continue )
          warn "keeping the local changes in ${DEST} and patching on top."
          ;;
        skip )
          SKIP_COMMIT=1
          break ;;
        abort )
          abort_port
          exit ${EXIT_ABORTED} ;;
        pause )
          pause_port "commit ${CMT_SHORT}, unexpected local changes in ${DEST}" ;;
      esac
    fi

    ANYTHING_TO_ADD=1

    TMP_CURRENT=$(mktemp -p "${TMP_WORK}" current_XXXXXX_${FILE_NAME})
    TMP_PARENT=$(mktemp -p "${TMP_WORK}" parent_XXXXXX_${FILE_NAME})

    cd "${TMP_ACPICA}" || die ${EXIT_ENV} "cannot enter ${TMP_ACPICA}."

    if ! git cat-file -p "${CMT}:${FILE}" > "$TMP_CURRENT" 2>/dev/null; then
      warn "${FILE} not found at ${CMT}! Skipping."
      rm -f "$TMP_CURRENT" "$TMP_PARENT" >/dev/null 2>&1 || true
      continue
    fi

    if ! git cat-file -p "${CMT}^:${FILE}" > "$TMP_PARENT" 2>/dev/null; then
        cat /dev/null > "$TMP_PARENT"
        info "Note: No parent file found for ${CMT}. New addition?"
    fi

    "${ACPISRC}" -ldqy "$TMP_PARENT" >> "${LOG_FILE}" 2>&1
    "${ACPISRC}" -ldqy "$TMP_CURRENT" >> "${LOG_FILE}" 2>&1
    clang-format -i --style="file:${TOOL_DIR}/clang-format" "$TMP_PARENT"
    clang-format -i --style="file:${TOOL_DIR}/clang-format" "$TMP_CURRENT"

    DEST_DIR="$(dirname -- "$DEST")"
    DIFF_RESULT=$(diff -u -E -p -B -b "$TMP_PARENT" "$TMP_CURRENT" || true)
    if [ -n "$DIFF_RESULT" ]; then
        # Probe first: does the patch apply cleanly without touching the tree?
        # -f on every invocation, not just the probe: without it, a reversed or
        # already-applied patch makes patch(1) ask its own questions ("Assume
        # -R?", "Apply anyway?") on /dev/tty. Since patch's output is redirected
        # to the log, that prompt is invisible and the run appears to hang; with
        # no terminal it instead takes the default and silently skips the hunk.
        # -f turns both cases into an ordinary failed hunk we already handle.
        if patch -l -F 3 -f --dry-run -d "${DEST_DIR}" "$FILE_NAME" <<< "$DIFF_RESULT" >> "${LOG_FILE}" 2>&1; then
            patch -l -F 3 -f -d "${DEST_DIR}" "$FILE_NAME" <<< "$DIFF_RESULT" >> "${LOG_FILE}" 2>&1
        else
            case "$(ask_conflict "Conflict: patch does not apply cleanly to ${DEST}.")" in
                continue )
                    warn "conflict: forcing the patch into ${DEST}."
                    patch -l -F 3 -f -d "${DEST_DIR}" "$FILE_NAME" <<< "$DIFF_RESULT" >> "${LOG_FILE}" 2>&1 || true
                    record_rejects "${DEST_DIR}" "${FILE_NAME}"
                    ANYTHING_REJECTED=1
                    ;;
                skip )
                    warn "conflict in ${DEST}: skipping commit ${CMT}."
                    SKIP_COMMIT=1
                    ;;
                abort )
                    err "conflict in ${DEST}: aborting."
                    abort_port
                    exit ${EXIT_ABORTED} ;;
                pause )
                    # The dry run created no .rej, so the failed patch exists
                    # nowhere on disk. Keep it in the log - which lives outside
                    # both repos - so the manual port has something to work from.
                    # Rewrite the diff headers, which name temporary files that
                    # are about to be deleted, so the saved patch is an ordinary
                    # -p1 patch against the kernel tree.
                    log "--- patch that failed to apply to ${DEST} (commit ${CMT}) ---"
                    log "$(printf '%s' "${DIFF_RESULT}" \
                          | sed -e "1s|^--- .*|--- a/${DST_REL}/${FILE_NAME}|" \
                                -e "2s|^+++ .*|+++ b/${DST_REL}/${FILE_NAME}|")"
                    log "--- end of patch ---"
                    warn "the patch that failed is saved in ${LOG_FILE}"
                    warn "  (apply it with: cd ${KERNEL_DIR} && patch -p1 < <the patch above>)"
                    pause_port "commit ${CMT_SHORT}, conflict in ${DEST}" ;;
            esac
        fi
    else
        warn "no changes applied on ${DEST}!"
    fi

    rm -f "$TMP_CURRENT" "$TMP_PARENT" >/dev/null 2>&1 || true

    if [[ "${SKIP_COMMIT}" != 0 ]]; then
        break
    fi

    cd "${KERNEL_DIR}" || die ${EXIT_ENV} "cannot enter ${KERNEL_DIR}."
    git add "${DEST}" >> "${LOG_FILE}" 2>&1 \
      || die ${EXIT_ENV} "git add failed for ${DEST}; see ${LOG_FILE}."
  done

  # If 'continue' was chosen on a conflict, pause so the user can resolve the
  # rejected hunks manually. Only reachable under -c ask and -c force.
  if [[ "${SKIP_COMMIT}" == 0 && "${ANYTHING_REJECTED}" != 0 ]]; then
    cd "${KERNEL_DIR}" || die ${EXIT_ENV} "cannot enter ${KERNEL_DIR}."
    case "$(ask_conflict "Commit ${CMT_SHORT} left rejected hunks (listed above); resolve them now if needed.")" in
      continue )
        info "Continuing..."
        # Whatever was resolved by hand is staged below; the reject files
        # themselves must not survive into the commit or the tree.
        delete_rejects
        git add -u >> "${LOG_FILE}" 2>&1 || true ;;
      skip )
        SKIP_COMMIT=1 ;;
      abort )
        abort_port
        exit ${EXIT_ABORTED} ;;
      pause )
        # The rejected hunks were already printed in full by record_rejects, so
        # the information survives the reset that pause_port performs.
        pause_port "commit ${CMT_SHORT}, rejected hunks left unresolved" ;;
    esac
  fi

  if [[ "${SKIP_COMMIT}" != 0 ]]; then
    skip_current_commit
    ((SKIPPED_CNTR++))
    info "Commit ${CMT}: skipped on conflict."
    continue
  fi

  if [[ "${ANYTHING_TO_ADD}" != 0 ]]; then
    if git commit --author="${MESSAGE_AUTHOR}" -m "${MESSAGE_NEW}" >> "${LOG_FILE}" 2>&1; then
      ((SERIE_CNTR++))
      LAST_PORTED="${CMT}"
      if [[ "${ANYTHING_REJECTED}" != 0 ]]; then
        ((PARTIAL_CNTR++))
        warn "Commit ${CMT}: committed with rejected hunks - review it before sending."
      fi
      info "Commit ${CMT}: ported and committed to '${BRANCH_NAME}'."
    else
      ((FAILED_CNTR++))
      warn "Commit ${CMT}: git commit failed (see ${LOG_FILE}); discarding its partial changes."
      # Leaving the changes staged would fold them into the next commit.
      skip_current_commit
    fi
  else
    info "Commit ${CMT}: no kernel relevant changes to port, skipping."
  fi

echo ""
done

if [[ "${BRANCH_EXISTED}" -eq 1 ]]; then
  BRANCH_STATE="updated"
else
  BRANCH_STATE="created"
fi
info "Branch '${BRANCH_NAME}' ${BRANCH_STATE} in ${KERNEL_DIR}. Processed ${#COMMITS[@]} commit(s) from ACPICA, ported ${SERIE_CNTR}, skipped ${SKIPPED_CNTR}, partial ${PARTIAL_CNTR}, failed ${FAILED_CNTR}."
info "Log: ${LOG_FILE}"

if (( SKIPPED_CNTR > 0 || PARTIAL_CNTR > 0 || FAILED_CNTR > 0 )); then
  exit ${EXIT_INCOMPLETE}
fi

exit ${EXIT_OK}
