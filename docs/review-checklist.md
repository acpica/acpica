# ACPICA Review Checklist

Use this checklist before requesting or approving review.

## Scope and risk

1. The diff is focused on one problem.
2. Unrelated files and formatting churn are excluded.
3. Behavior changes are intentional and explained.

## Correctness

1. Length, offset, and count handling is safe for parser changes.
2. Failure paths emit useful diagnostics.
3. No obvious regression in surrounding logic.

## Style and maintainability

1. New or modified lines follow local style and alignment.
2. New lines stay near or below 80 columns when practical.
3. Comments are concise and explain intent.

## Validation evidence

1. Build result is included.
2. Round-trip verification is included when relevant.
3. Broader test status is noted when applicable.
