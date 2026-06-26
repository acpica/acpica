# ACPICA Style Guide

This guide favors readability and consistency.

## Core rules

1. Try to keep the character count up to or below 80 per line as much as you
   can, with a few rare exceptions in case of avoiding ugly or hard to follow
   code.
2. Follow existing spacing and alignment in surrounding code.
3. Preserve local naming patterns unless there is a strong reason to refactor.
4. Keep comments brief and useful.
5. Avoid unrelated formatting churn in functional patches.

## Parser and table code style

1. Prefer clear fail-fast checks for invalid lengths and offsets.
2. Emit concise diagnostics with useful values such as offset and length.
3. Keep validation logic small and focused on safety and clarity.
