#!/bin/sh
#
# Generate acpiexec utility
#

mkdir -p bin
cp Acpi/generate/linux/Makefile.acpiexec Acpi/source/tools/acpiexec/Makefile
cp Acpi/source/os_specific/service_layers/osunixxf.c Acpi/source
cd Acpi/source/tools/acpiexec
make
cp acpiexec ../../../../bin
