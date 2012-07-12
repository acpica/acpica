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

if [ -z $1 ] ; then
	echo "Usage: $0 <Linux>"
	echo "  Linux: Path of Linux source"
	exit 1
fi

# Get the root of the ACPICA source tree
ACPICA=`readlink -f ../..`

LINUX=$1
LINDENT=$ACPICA/generate/linux/patches/lindent.sh
ACPICA_TMP=acpica_tmp
LINUX_ACPICA=linux-acpica
ACPICA_LINUXIZED=acpica-linuxized

#
# Build the AcpiSrc utility if necessary
#
echo "Ensure the 32-bit AcpiSrc utility is up-to-date"
make -C $ACPICA BITS=32 acpisrc
ACPISRC=${ACPICA}/generate/unix/acpisrc/obj32/acpisrc

#
# Copy the actual Linux ACPICA files locally
#
echo "Create local Linux ACPICA files subdirectory"
rm -rf $ACPICA_TMP $LINUX_ACPICA $ACPICA_LINUXIZED
mkdir $ACPICA_TMP $LINUX_ACPICA

cp $LINUX/drivers/acpi/acpica/* $LINUX_ACPICA/
cp $LINUX/include/acpi/*.h $LINUX_ACPICA/
cp $LINUX/include/acpi/platform/*.h $LINUX_ACPICA/

#
# Ensure that the files in the two directories match
#
cd $LINUX_ACPICA
ALL_FILES=`ls`

for f in $ALL_FILES ; do
	tmp_f=`find $ACPICA/source -name $f`
	if [ ! -z $tmp_f ] ; then
		cp $tmp_f ../$ACPICA_TMP
	else
		rm $f
	fi
done

#
# Linuxize the ACPICA source
#
cd ..
$ACPISRC -ldqy $ACPICA_TMP $ACPICA_LINUXIZED

#
# Enable cross platform generation
#
d2u -q $LINDENT
d2u -q $ACPICA_LINUXIZED/*
d2u -q $LINUX_ACPICA/*

#
# Lindent both sets of files
#
echo "Build lindented linuxized ACPICA files"
cd $ACPICA_LINUXIZED
find . -name "*.[ch]" | xargs $LINDENT
rm -f *~
cd ..

echo "Build lindented actual linux ACPICA files"
cd $LINUX_ACPICA
find . -name "*.[ch]" | xargs $LINDENT
rm -f *~
cd ..

#
# Now we can finally do the big diff
#
echo "Create ACPICA/Linux diff"
diff -E -b -w -B -rpuN $LINUX_ACPICA $ACPICA_LINUXIZED > divergence.diff
ls -l divergence.diff

#
# Cleanup
#
rm -r $LINUX_ACPICA
rm -r $ACPICA_TMP
rm -r $ACPICA_LINUXIZED
