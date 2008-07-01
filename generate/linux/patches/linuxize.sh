#!/bin/sh
#
# Create linuxized ACPICA source
#

# Convert ACPICA source to Linux format

version=$1
branch=master

if [ ! -z "$version" ] ; then
	cd acpica
	git checkout $version
	cd ..
fi

rm -rf new.linux
bin/acpisrc -ldqy acpica/source new.linux
cd new.linux


# delete the various cvs control directories and files
# <no longer needed>
#
#find . -name cvs | xargs rm -rf


# Update #include statements in all source files
# <no longer needed>
#
#for file in `find . -name "*.[ch]"`; do
#    sed -r -e 's|#include "(.+)"|#include <acpi/\1>|g' < $file > $file.tmp ; mv $file.tmp $file
#done


# flatten the ACPICA directory structure

mv components/* .


# delete all directories that are not needed by Linux

rm -rf common compiler components debugger disassembler interpreter os_specific tools


#
# create the expected Linux directory structure
# 1) Move all ACPICA include files to include/acpi
# 2) Move all ACPICA code to drivers/acpi
#
mkdir -p acpi_include
mv -f include/* acpi_include
mv -f acpi_include include/acpi

mkdir -p drivers/acpi
mv dispatcher events executer hardware namespace parser resources tables utilities drivers/acpi/


# indent all .c and .h files

find . -name "*.[ch]" | xargs ../lindent.sh


# cleanup backup files made by indent

find . -name "*~" | xargs rm -f
