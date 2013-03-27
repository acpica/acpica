#!/bin/sh
#
# Create linuxized ACPICA source
#

# Convert ACPICA source to Linux format


gen_acpisrc=no

usage()
{
	echo "Usage:"
	echo "`basename $0` [-s] <repository> [commit]"
	echo "Where:"
	echo "        -s: generate acpisrc"
	echo "repository: git repository directory"
	echo "    commit: git commit id"
	exit -1
}

while getopts "s" opt
do
	case $opt in
	s) gen_acpisrc=yes;;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

git_root=$1
version=$2

if [ -z "$git_root" ] ; then
	usage
fi

branch=master

if [ ! -z "$version" ] ; then
	(
		cd $git_root
		git reset --hard $version >/dev/null 2>&1
	)
fi

# Generate latest version of the acpisrc utility

if [ "x$gen_acpisrc" = "xyes" ]; then
	echo "[linuxize.sh] Generate acpisrc utility from source"
	sh acpisrc.sh $git_root > /dev/null
fi

rm -rf new.linux
echo "[linuxize.sh] Coverting format (AcpiSrc)..."
bin/acpisrc -ldqy $git_root/source new.linux > /dev/null
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
echo "[linuxize.sh] Coverting hierarchy (drivers/acpi/acpica|include/acpi)..."
mkdir -p acpi_include
mv -f include/* acpi_include
mv -f acpi_include include/acpi

mkdir -p drivers/acpi/acpica
mv dispatcher/* events/* executer/* hardware/* namespace/* parser/* resources/* tables/* utilities/* drivers/acpi/acpica
rm -rf dispatcher events executer hardware namespace parser resources tables utilities

private_includes="accommon.h"
private_includes="$private_includes acdebug.h acdispat.h"
private_includes="$private_includes acevents.h"
private_includes="$private_includes acglobal.h"
private_includes="$private_includes achware.h"
private_includes="$private_includes acinterp.h"
private_includes="$private_includes aclocal.h"
private_includes="$private_includes acmacros.h"
private_includes="$private_includes acnamesp.h"
private_includes="$private_includes acobject.h acopcode.h"
private_includes="$private_includes acparser.h acpredef.h"
private_includes="$private_includes acresrc.h"
private_includes="$private_includes acstruct.h"
private_includes="$private_includes actables.h"
private_includes="$private_includes acutils.h"
private_includes="$private_includes amlcode.h amlresrc.h"
for inc in $private_includes ; do
	mv include/acpi/$inc drivers/acpi/acpica/
done

# indent all .c and .h files
echo "[linuxize.sh] Converting format (lindent.sh)..."
find . -name "*.[ch]" | xargs ../lindent.sh


# cleanup backup files made by indent

find . -name "*~" | xargs rm -f
