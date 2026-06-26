# Table Parser Validation

This guide defines a minimal, high-value validation approach.

## Philosophy

1. Add checks that prevent bad traversal or misleading decode output.
2. Avoid adding large volumes of defensive code for low-probability cases.
3. Prefer diagnostics that help firmware and tool developers debug quickly.

## Recommended checks

1. Validate fixed headers before dereference.
2. Validate declared lengths against remaining table bytes.
3. Validate count-based arrays fit in remaining bytes before iteration.
4. Reject zero or invalid lengths that could cause loop or offset issues.

## Diagnostic quality

1. Include offset, declared length or count, and available bytes.
2. Use concise messages with consistent format.
3. Stop parsing when continued traversal is unsafe.
