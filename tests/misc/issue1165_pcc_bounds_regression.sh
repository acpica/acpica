#!/usr/bin/env bash
set -euo pipefail

# Standalone negative regression test for issue #1165.
# It verifies the PCC field bounds check in AcpiExReadDataFromField.

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
ACPICEXEC_DEFAULT="$ROOT_DIR/generate/unix/bin/acpiexec"
ACPIEXEC_BIN="${1:-${acpiexec:-$ACPICEXEC_DEFAULT}}"

if [[ ! -x "$ACPIEXEC_BIN" ]]; then
    echo "SKIP: acpiexec not found/executable at: $ACPIEXEC_BIN"
    exit 0
fi

WORKDIR="$(mktemp -d)"
trap 'rm -rf "$WORKDIR"' EXIT

AML_PATH="$WORKDIR/issue1165.aml"
OUT_PATH="$WORKDIR/issue1165.out"

cat > "$WORKDIR/issue1165.hex" <<'EOF_HEX'
44534454a40000000266525553544655414d4c46555a5a52010000005253465401000000084d41494eff5b804d5952450a09ff7f010a800a805b810c4d5952450046494c4445047046494c44085245535f0d5858585858005b207146494c4460efbf605245535f4348454b0d48656c6c6f00860d5858585858005245535f5b28716067707161930d576f726c640046494c447083625245535f4348454b0d576f726c6400
EOF_HEX

xxd -r -p "$WORKDIR/issue1165.hex" "$AML_PATH"

ASAN_OPTIONS="${ASAN_OPTIONS:-detect_leaks=0}" "$ACPIEXEC_BIN" -m "$AML_PATH" \
    > "$OUT_PATH" 2>&1 || true

if grep -q "AddressSanitizer: heap-buffer-overflow" "$OUT_PATH"; then
    echo "FAIL: ASAN heap-buffer-overflow reproduced"
    sed -n '1,160p' "$OUT_PATH"
    exit 1
fi

if ! grep -q "PCC field at offset" "$OUT_PATH"; then
    echo "FAIL: Expected PCC bounds-check diagnostic not found"
    sed -n '1,160p' "$OUT_PATH"
    exit 1
fi

echo "PASS: Issue 1165 PCC field bounds regression test"
echo "PASS: No ASAN heap-buffer-overflow detected"
