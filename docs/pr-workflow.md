# ACPICA PR Workflow

This workflow keeps changes reviewable and low risk.

## Branching

1. Use a dedicated branch per PR topic.
2. Keep unrelated local files out of the patch whenever possible.

## Implementation flow

1. Scope the change and update only relevant files.
2. Validate build and focused tests.
3. Draft commit locally with clear verification notes.
4. Include required signature trailers.
5. Push after final review and confirmation.

## Review readiness checklist

1. Minimal diff for the stated problem.
2. No style drift beyond touched logic.
3. Relevant tests or round-trip verification included.
4. Commit message clearly states what changed and why.
