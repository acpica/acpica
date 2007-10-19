#!/bin/sh
#
# Generate acpisrc utility
#

mkdir -p bin
cp Acpi/generate/linux/Makefile.acpisrc Acpi/source/tools/acpisrc/Makefile
cp Acpi/source/os_specific/service_layers/osunixdir.c Acpi/source/tools/acpisrc
make -C Acpi/source/tools/acpisrc
cp Acpi/source/tools/acpisrc/acpisrc /bin
