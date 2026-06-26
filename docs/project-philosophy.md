# ACPICA Project Philosophy

This guide defines high-level engineering principles for ACPICA.

## Portability first

1. Keep ACPICA portable across supported environments.
2. Changes should build and run on Unix-like and Windows toolchains.
3. Avoid introducing platform-specific behavior unless required and isolated.

## C language and implementation constraints

1. Maintain compatibility with both older and newer C standards used by
   supported toolchains.
2. Avoid dependencies on non-standard language extensions when practical.
3. Avoid unnecessary reliance on external C libraries beyond established
   project usage.

## Build quality and compiler discipline

1. Keep builds clean across supported environments.
2. Use strict compiler checking, including warning-focused configurations such
   as `W=1`, when validating changes.
3. Treat new warnings as regressions unless there is a justified exception.

## ACPI specification conformance

1. Implement ACPI behavior in line with the specification whenever practical.
2. Prioritize correctness, interoperability, and long-term maintainability.
3. In rare cases, allow pragmatic deviations when strict implementation would
   break a supported environment or create unacceptable portability risk.
4. When such deviations are made, document the tradeoff and rationale clearly.

## Practical engineering balance

1. Prefer minimal, high-value changes over broad rewrites.
2. Keep diagnostics useful and concise.
3. Optimize for maintainable code that future contributors can reason about
   quickly.
