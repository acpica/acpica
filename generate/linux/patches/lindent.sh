#!/bin/sh
#
# Standard source indent
#
indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -T u8 -T u16 -T u32 -T u64 -T acpi_integer -T acpi_predefined_data -T acpi_operand_object -T acpi_event_status "$@"
