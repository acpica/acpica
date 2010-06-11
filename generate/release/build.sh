#******************************************************************************
#
# ACPICA release generation script for Windows execution
#
#              $Revision: 1.64 $
#
# Requires cygwin be installed - http://www.cygwin.com
# and its /bin be *first* in your path
# Also requires pkzip25.
#
# Execute this script from the top level ACPI source directory.
#
# Parameters: notests - do not generate test source code package
#
#******************************************************************************

PKZIP="c:/command/pkzip.exe"

#
# Move and preserve any previous versions of the various release packages
#
echo Moving previous release to archive
mkdir -p current
mkdir -p archive
#
# Save any older versions of the release packages
#
mv current/* archive
echo Completed save of previous release

#
# cd from acpica/generate/release to acpica
cd ../..


#
# Ensure that the temporary directories are created fresh
#
rm -rf wintemp
rm -rf unixtemp
rm -rf acpica-unix-`date +%Y%m%d`

#******************************************************************************
#
# Unix source code package
#
#******************************************************************************
echo
echo ACPICA - Unix source code package
echo

#
# Make temp directories
#
mkdir -p unixtemp/generate
mkdir -p unixtemp/tools
mkdir -p unixtemp/os_specific
mkdir -p unixtemp/tests
mkdir -p unixtemp/tests/misc
mkdir -p unixtemp/tests/templates

#
# Copy ACPICA subsystem source code
#
cp -r documents/changes.txt unixtemp/changes.txt
cp -r source/common unixtemp/common
cp -r source/components/* unixtemp
cp -r source/include unixtemp/include

#
# iASL compiler source
#
cp -r source/compiler unixtemp/compiler

#
# ACPICA tools source
#
cp -r source/tools/acpisrc unixtemp/tools
cp -r source/tools/acpiexec unixtemp/tools
cp -r source/tools/acpixtract unixtemp/tools
cp -r source/tools/examples unixtemp/tools

#
# iASL/ACPICA miscellaneous tests (not full test suites)
#
cp -r tests/misc/*.asl unixtemp/tests/misc
cp -r tests/templates/Makefile unixtemp/tests/templates
cp -r tests/templates/templates.sh unixtemp/tests/templates

#
# OS-specific interfaces
#
cp -r source/os_specific/service_layers unixtemp/os_specific/service_layers
cp source/os_specific/service_layers/osunixxf.c unixtemp
cp source/os_specific/service_layers/osunixdir.c unixtemp/tools/acpisrc
cp source/os_specific/service_layers/osunixdir.c unixtemp/tools/acpiexec

#
# Copy UNIX makefiles
#
cp generate/linux/Makefile.iasl unixtemp/compiler/Makefile
cp generate/linux/Makefile.acpisrc unixtemp/tools/acpisrc/Makefile
cp generate/linux/Makefile.acpiexec unixtemp/tools/acpiexec/Makefile
cp generate/linux/Makefile.acpixtract unixtemp/tools/acpixtract/Makefile
cp generate/linux/README.acpica-unix unixtemp/README

#
# Copy Lint directory, delete extraneous files
#
cp -r generate/lint unixtemp/generate/lint
rm -f unixtemp/generate/lint/co*
rm -f unixtemp/generate/lint/env*
rm -f unixtemp/generate/lint/lib*
rm -f unixtemp/generate/lint/LintOut.txt

#
# Delete extraneous files
#
cd unixtemp
find . -name "*.scc"|xargs rm -f
find . -name "CVS"|xargs rm -r -f

#
# Convert all LF/CR pairs to Unix format (LF only)
#
echo Start LF/CR Conversion
find . -name "*"|xargs d2u
echo LF/CR Conversion complete
cd ..

#
# Build release package
#
mv unixtemp acpica-unix-`date +%Y%m%d`
tar czf acpica-unix-`date +%Y%m%d`.tar.gz acpica-unix-`date +%Y%m%d`

#
# Move the completed package
#
mv acpica-unix-`date +%Y%m%d`.tar.gz generate/release/current

#
# Remove the temporary directory
#
rm -rf acpica-unix-`date +%Y%m%d`


#******************************************************************************
#
# Windows source code package
#
#******************************************************************************
echo
echo ACPICA - Windows source code package
echo

#
# Make temp directories
#
mkdir wintemp
mkdir wintemp/libraries
mkdir -p wintemp/generate/msvc
mkdir -p wintemp/source/os_specific/service_layers
mkdir -p wintemp/tests
mkdir -p wintemp/tests/misc
mkdir -p wintemp/tests/templates

#
# Copy ACPICA subsystem source code
#
cp -r documents/changes.txt wintemp/changes.txt
cp -r source/common wintemp/source/common
cp -r source/components wintemp/source/
cp -r source/include wintemp/source/include

#
# iASL compiler source
#
cp -r source/compiler wintemp/source/compiler

#
# ACPICA tools source
#
cp -r source/tools wintemp/source/tools

#
# iASL/ACPICA miscellaneous tests (not full test suites)
#
cp -r tests/misc/*.asl wintemp/tests/misc
cp -r tests/templates/Makefile wintemp/tests/templates
cp -r tests/templates/templates.sh wintemp/tests/templates

#
# Copy all OS-specific interfaces
#
cp source/os_specific/service_layers/*.c wintemp/source/os_specific/service_layers

#
# Copy project files for MS VC++ (6.0)
#
cp -r generate/msvc/*.dsp wintemp/generate/msvc/
cp -r generate/msvc/*.dsw wintemp/generate/msvc/

#
# Copy Lint directory, delete extraneous files
#
cp -r generate/lint wintemp/generate/lint
rm -f wintemp/generate/lint/co*
rm -f wintemp/generate/lint/env*
rm -f wintemp/generate/lint/lib*
rm -f wintemp/generate/lint/LintOut.txt

#
# Delete extraneous files
#
cd wintemp
find . -name "*.scc"|xargs rm -f
find . -name "*.ncb"|xargs rm -f
find . -name "*.opt"|xargs rm -f
find . -name "CVS"|xargs rm -r -f

#
# Build release package
#
$PKZIP -add -max -dir -sort=name ../generate/release/current/acpica-win-`date +%Y%m%d`
cd ..

#
# Remove temporary directory
#
rm -rf wintemp


#******************************************************************************
#
# Windows iASL executable package
#
#******************************************************************************
echo
echo iASL Compiler - Windows executable package
echo

#
# Make temp directory
#
mkdir wintemp

#
# Copy executables and documentation
#
cp -r documents/changes.txt wintemp/changes.txt
cp documents/aslcompiler.pdf wintemp
cp libraries/iasl.exe wintemp
cp libraries/acpixtract.exe wintemp
cp libraries/acpiexec.exe wintemp
cp libraries/acpisrc.exe wintemp
cp tests/misc/badcode.asl wintemp

#
# Build release package
#
cd wintemp
$PKZIP -add -max -dir -sort=name ../generate/release/current/iasl-win-`date +%Y%m%d`
cd ..

#
# Remove temporary directory
#
rm -rf wintemp


#******************************************************************************
#
# Source code release (email) package
# Contains: iASL executable, unix source package, and changes.txt file
#
# This zipfile is created with a password so that it can be safely emailed
# without interference from overzealous email scanners.
# Password is acpica
#
#******************************************************************************
echo
echo ACPICA - Source code release package
echo

cp documents/changes.txt generate/release/current/changes.txt
cd generate/release/current
$PKZIP -add -max -password=acpica acpica-release-`date +%Y%m%d` changes.txt iasl-win-`date +%Y%m%d`.zip acpica-unix-`date +%Y%m%d`.tar.gz
rm changes.txt
cd ../../..


#******************************************************************************
#
# Exit now if "notests" option specified
#
#******************************************************************************
if [ "$1" = notests ]
then
    echo APCICA test suites will not be generated
    exit 0;
fi


#******************************************************************************
#
# Unix ASL Test source code package
#
#******************************************************************************
echo
echo ACPICA - Unix ASL Test source code package
echo

#
# Make temp directory
#
mkdir unixtemp

#
# ASL Test source
#
cp -r tests unixtemp/tests

#
# Delete extraneous files
#
cd unixtemp
find . -name "tmp"|xargs rm -r -f
find . -name "CVS"|xargs rm -r -f
cd ..

#
# Convert all LF/CR pairs to Unix format (LF only)
#
echo Start LF/CR Conversion
cd unixtemp
find . -name "*"|xargs d2u
echo LF/CR Conversion complete
cd ..

#
# Build release package
#
mv unixtemp acpitests-unix-`date +%Y%m%d`
tar czf acpitests-unix-`date +%Y%m%d`.tar.gz acpitests-unix-`date +%Y%m%d`

#
# Move the completed package
#
mv acpitests-unix-`date +%Y%m%d`.tar.gz generate/release/current

#
# Remove the temporary directory
#
rm -rf acpitests-unix-`date +%Y%m%d`


#******************************************************************************
#
# Windows ASL Test source code package
#
#******************************************************************************
echo
echo ACPICA - Windows ASL Test source code package
echo

#
# Make temp directory
#
mkdir wintemp

#
# ASL Test source
#
cp -r tests wintemp/tests

#
# Delete extraneous files
#
cd wintemp
find . -name "tmp"|xargs rm -r -f
find . -name "CVS"|xargs rm -r -f
cd ..

#
# Build release package
#
cd wintemp
$PKZIP -add -max -dir -sort=name ../generate/release/current/acpitests-win-`date +%Y%m%d`
cd ..

#
# Remove temporary directory
#
rm -rf wintemp


date

