#!/bin/sh
#
# Generate acpisrc utility
#

mkdir -p bin
cp acpica/generate/linux/Makefile.acpisrc acpica/source/tools/acpisrc/Makefile
cp acpica/source/os_specific/service_layers/osunixdir.c acpica/source/tools/acpisrc
make -C acpica/source/tools/acpisrc
cp acpica/source/tools/acpisrc/acpisrc bin
