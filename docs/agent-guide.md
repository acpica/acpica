# ACPICA Agent Guide

This guide helps AI coding agents contribute consistently.

## Working style

1. Prefer minimal, high-value changes over broad defensive rewrites.
2. Preserve local formatting and alignment in touched code.
3. Keep new or modified lines near or below 80 columns when practical.
4. Avoid unrelated refactors during bug fixes.

## Safety for parser and table code

1. Add checks that prevent unsafe traversal and misleading decode output.
2. Prefer concise diagnostics with offset and size details.
3. Stop parsing when bounds are invalid.

## Verification expectations

1. Build before proposing push.
2. Use template-based round trip for compiler/disassembler table changes.
3. Report exact result and any limitations.

## Branch and commit flow

1. Use dedicated branches per topic.
2. Draft commits locally first.
3. Push only after explicit confirmation.
