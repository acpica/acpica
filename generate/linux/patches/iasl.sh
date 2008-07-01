#!/bin/sh
#
# Generate iASL compiler
#

mkdir -p bin
cp Acpi/generate/linux/Makefile.iasl Acpi/source/compiler/Makefile
cp Acpi/source/os_specific/service_layers/osunixxf.c Acpi/source
cd Acpi/source/compiler
make
cp iasl ../../../bin
