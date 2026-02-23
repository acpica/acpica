#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../../.." && pwd)"

IASL="${REPO_ROOT}/generate/unix/bin/iasl"
ACPIEXEC="${REPO_ROOT}/generate/unix/bin/acpiexec"
ASL_FILE="${SCRIPT_DIR}/dsmtest.asl"
AML_FILE="${SCRIPT_DIR}/dsmtest.aml"

"${IASL}" -tc "${ASL_FILE}"

OUTPUT="$("${ACPIEXEC}" -b "evaluate \\_SB.DUT0.TDSM" "${AML_FILE}")"
printf '%s\n' "${OUTPUT}"

if grep -q "\[Integer\] = 000000000000000F" <<<"${OUTPUT}"; then
    echo "PASS: _DSM Arg3 accepted all 4 tested types (Package/String/Buffer/Integer)."
else
    echo "FAIL: Expected return value 0x0F was not observed." >&2
    exit 1
fi
