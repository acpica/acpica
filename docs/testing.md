# ACPICA Testing Guide

Use the smallest test set that provides confidence for the change.

## Baseline checks

1. Build the tree and confirm no new build errors.
2. For table compiler/disassembler changes, run template-based round trip:
   ASL to AML to DSL to AML.
3. Compare AML outputs and report whether they match exactly.
4. If needed, compare with checksum byte normalized to confirm semantic match.

## Broader checks

1. Run ASLTS or other broader suites when risk is medium or high.
2. If broad tests are skipped, note why in commit or PR notes.

## What to record in commit or PR notes

1. Build result.
2. Round-trip result.
3. Any test limitations or assumptions.
4. Reason for the change(s)
5. Any future scope applicable in this area
