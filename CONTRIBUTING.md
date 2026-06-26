# Contributing to ACPICA

This file is a short, practical guide for contributors.

## Contribution flow

1. Create a dedicated branch for each topic or pull request.
2. Keep changes minimal and focused on one problem.
3. Build and run relevant verification before pushing.
4. Draft commits locally first.
5. Push only after you are ready for review OR mark your PR as "draft" if it is still WIP.

## Commit guidance

1. Use clear commit titles with subsystem and intent.
2. Include what changed, why, and how it was verified.
3. Include author signature trailers as required by the project process.

## Code review guidance

1. Prioritize behavior and regression risks over style-only feedback.
2. For parser code, validate boundary handling and diagnostics.
3. Prefer high-value checks over defensive bloat.

## Validation expectations

1. Confirm build succeeds.
2. Run table-specific round-trip checks when touching compiler/disassembler
   logic.
3. Run broader tests when appropriate for scope and risk.

For detailed rules, see:

1. docs/style.md
2. docs/testing.md
3. docs/table-parser-validation.md
4. docs/pr-workflow.md
