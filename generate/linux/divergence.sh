#!/bin/bash
#
# Script to find the divergences between these sets of source code:
#    1) The current ACPICA source from the ACPICA git tree
#    2) The version of ACPICA that is integrated into Linux
#
# The goal is to eliminate as many differences as possible between
# these two sets of code.
#
# Usage: ./divergence.sh <Path to root of linux source code>
#

usage () {
	echo "Usage: `basename $0` [-s] <path>"
	echo "Where:"
	echo "  -s: indent on (Linux) rather than on (Linux and ACPICA)"
	echo "  path is path to root of Linux source code."
	return 0
}

while getopts "s" opt
do
	case $opt in
	s) LINDENT_DIR=single;;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

HARDWARE_NAME=`uname -m`
BINDIR=not_initialized
ACPICA_TMP=acpica_tmp
LINUX_ACPICA=linux-acpica
ACPICA_LINUXIZED=acpica-linuxized

# Get the root of the ACPICA source tree
ACPICA=`readlink -f ../..`
LINDENT=$ACPICA/generate/linux/patches/lindent.sh
LINUX=$1


# Parameter validation

if [ -z $1 ] ; then
	echo "Usage: $0 <Linux>"
	echo "  Linux: Path of Linux source"
	return 1
fi
if [ ! -e $1 ] ; then
	echo "$1, Linux source directory does not exist"
	return 1
fi
if [ ! -d $1 ] ; then
	echo "$1, Not a directory"
	return 1
fi

if [ ! -e $LINDENT ] ; then
	echo "Could not find lindent.sh script"
	return 1
fi
if [ -z $LINDENT_DIR ] ; then
	LINDENT_DIR=multiple
fi

#
# Determine if we are on a 32-bit or 64-bit OS.
# Any machine hardware name containing a substring "64" is
# considered to be a 64-bit platform (such as x86_64).
#
get_platform_bitwidth () {

	case "$HARDWARE_NAME" in
		*64* ) WIDTH=64;;
		*    ) WIDTH=32;;
	esac

	BINDIR=bin$WIDTH
	WIDTHNAME=$WIDTH-bit
}

#
# Build the AcpiSrc utility if necessary, in the native
# width of the platform.
#
get_platform_bitwidth
echo "Ensure the $WIDTHNAME AcpiSrc utility is up-to-date on platform type $HARDWARE_NAME"
make -C $ACPICA BITS=$WIDTH acpisrc
ACPISRC=${ACPICA}/generate/unix/$BINDIR/acpisrc

#
# Copy the actual Linux ACPICA files locally (from the Linux tree)
#
echo "Creating local Linux ACPICA files subdirectory"
rm -rf $ACPICA_TMP $LINUX_ACPICA $ACPICA_LINUXIZED
mkdir $ACPICA_TMP $LINUX_ACPICA

mkdir -p $LINUX_ACPICA/drivers/acpi/acpica
cp $LINUX/drivers/acpi/acpica/* $LINUX_ACPICA/drivers/acpi/acpica/
mkdir -p $LINUX_ACPICA/include/acpi/platform
cp $LINUX/include/acpi/*.h $LINUX_ACPICA/include/acpi/
cp $LINUX/include/acpi/platform/*.h $LINUX_ACPICA/include/acpi/platform/

#
# Ensure that the files in the two directories
# (native ACPICA and Linux ACPICA) match
#

ALL_FILES=`find $LINUX_ACPICA`

for t in $ALL_FILES ; do
	if [ -f $t ] ; then
		d=$ACPICA_TMP`dirname ${t#${LINUX_ACPICA}}`
		f=`find $ACPICA/source -name \`basename $t\``
		if [ ! -z $f ] ; then
			mkdir -p $d
			cp -f $f $d
		else
			rm -f $t
		fi
	fi
done

# Do we need to perform things on private_includes?
private_includes="accommon.h acdebug.h acevents.h achware.h aclocal.h acnamesp.h acopcode.h acpredef.h acstruct.h acutils.h amlresrc.h"
private_includes="$private_includes acconfig.h acdispat.h acglobal.h acinterp.h acmacros.h acobject.h acparser.h acresrc.h actables.h amlcode.h"
for inc in $private_includes ; do
	if [ -f $ACPICA_TMP/include/acpi/$inc ] ; then
		echo "Warning: private include file $inc is now public.  Please check the linuxize.sh"
	elif [ ! -f $ACPICA_TMP/drivers/acpi/acpica/$inc ] ; then
		echo "Warning: private include file $inc does not exist.  Please check the linuxize.sh."
	fi
done

#
# Linuxize the ACPICA source
#
echo "Linuxizing the ACPICA source code:"
$ACPISRC -ldqy $ACPICA_TMP $ACPICA_LINUXIZED

#
# Enable cross platform generation
#
dos2unix -q $LINDENT
find $ACPICA_LINUXIZED | xargs dos2unix -q
find $LINUX_ACPICA | xargs dos2unix -q

#
# Lindent both sets of files
#
echo "Building lindented linuxized ACPICA files"
find $ACPICA_LINUXIZED -name "*.[ch]" | xargs $LINDENT
find $ACPICA_LINUXIZED -name *~ | xargs rm -f

if [ "x$LINDENT_DIR" = "xmultiple" ] ; then
	echo "Building lindented actual linux ACPICA files"
	find $LINUX_ACPICA -name "*.[ch]" | xargs $LINDENT
	find $LINUX_ACPICA -name *~ | xargs rm -f
fi

#
# Now we can finally do the big diff
#
echo "Creating ACPICA/Linux diff"
diff -E -b -w -B -rpuN $LINUX_ACPICA $ACPICA_LINUXIZED > divergence-$LINDENT_DIR.diff
diffstat divergence-$LINDENT_DIR.diff > diffstat-$LINDENT_DIR.txt
ls -l divergence-$LINDENT_DIR.diff diffstat-$LINDENT_DIR.txt

#
# Cleanup
#
rm -r $LINUX_ACPICA
rm -r $ACPICA_TMP
rm -r $ACPICA_LINUXIZED
return 0
