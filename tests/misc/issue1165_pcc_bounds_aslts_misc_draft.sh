#!/usr/bin/env bash
set -euo pipefail

# ASLTS-style draft wrapper for issue #1165.
# This intentionally mirrors a runtime test status line format to ease
# migration into an ASLTS misc/bdemo collection later.

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
STANDALONE_TEST="$SCRIPT_DIR/issue1165_pcc_bounds_regression.sh"

if [[ ! -x "$STANDALONE_TEST" ]]; then
    echo "ACPI Debug:  \":STST:complex:misc:issue1165:FAIL:Standalone draft script missing:\""
    exit 1
fi

if "$STANDALONE_TEST" "${1:-}" >/tmp/issue1165_pcc_bounds_aslts_draft.log 2>&1; then
    echo "ACPI Debug:  \":STST:complex:misc:issue1165:PASS:\""
    exit 0
fi

echo "ACPI Debug:  \":STST:complex:misc:issue1165:FAIL:See /tmp/issue1165_pcc_bounds_aslts_draft.log:\""
sed -n '1,120p' /tmp/issue1165_pcc_bounds_aslts_draft.log
exit 1
