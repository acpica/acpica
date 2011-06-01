#******************************************************************************
#
# ACPICA release generation script for Cygwin/Windows execution
#
# Requires cygwin be installed - http://www.cygwin.com
# and its /bin be *first* in your path.
#
# Also requires pkzip25 (free, available at ftp://ftp.onego.ru/pkzip/pkzip25.exe
# and other places - search for "pzkzip25")
#
# Execute this script from the top level ACPI source directory.
#
# Parameters: notests - do not generate test source code package
#
#******************************************************************************

PKZIP="c:/command/pkzip25.exe"

#
# Move and preserve any previous versions of the various release packages
#
echo Moving previous release to archive
mkdir -p current
mkdir -p archive

#
# Save any older versions of the release packages
#
for file in current/*
do
    if [ -f $file ]; then
        cp $file archive
        rm $file
        echo moved $file to archive
    fi
done
echo Completed save of previous release to archive

#
# cd from acpica/generate/release to acpica
#
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
cp -r source/tools/acpinames unixtemp/tools
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
# Copy Linux/UNIX makefiles
#
cp generate/linux/Makefile.iasl unixtemp/compiler/Makefile
cp generate/linux/Makefile.acpisrc unixtemp/tools/acpisrc/Makefile
cp generate/linux/Makefile.acpiexec unixtemp/tools/acpiexec/Makefile
cp generate/linux/Makefile.acpihelp unixtemp/tools/acpihelp/Makefile
cp generate/linux/Makefile.acpinames unixtemp/tools/acpinames/Makefile
cp generate/linux/Makefile.acpixtract unixtemp/tools/acpixtract/Makefile
cp generate/linux/README.acpica-unix unixtemp/README

#
# Copy generic UNIX makefiles
#
mkdir -p unixtemp/generate/unix
mkdir -p unixtemp/generate/unix/acpiexec
mkdir -p unixtemp/generate/unix/acpihelp
mkdir -p unixtemp/generate/unix/acpinames
mkdir -p unixtemp/generate/unix/acpisrc
mkdir -p unixtemp/generate/unix/acpixtract
mkdir -p unixtemp/generate/unix/iasl
mkdir -p unixtemp/generate/unix/bin

cp generate/unix/readme.txt unixtemp/generate/unix/readme.txt
cp generate/unix/Makefile* unixtemp/generate/unix
cp generate/unix/acpiexec/Makefile unixtemp/generate/unix/acpiexec
cp generate/unix/acpihelp/Makefile unixtemp/generate/unix/acpihelp
cp generate/unix/acpinames/Makefile unixtemp/generate/unix/acpinames
cp generate/unix/acpisrc/Makefile unixtemp/generate/unix/acpisrc
cp generate/unix/acpixtract/Makefile unixtemp/generate/unix/acpixtract
cp generate/unix/iasl/Makefile unixtemp/generate/unix/iasl

#
# Copy Lint directory
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
rm -rf unixtemp


#******************************************************************************
#
# Unix source code package with dual-license
#
#******************************************************************************
echo
echo ACPICA - Dual-license Unix source code package
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
cp -r source/tools/acpihelp unixtemp/tools
cp -r source/tools/acpinames unixtemp/tools
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
# Insert the dual-license into *.c and *.h files
#
libraries/acpisrc -h -y unixtemp

#
# Copy Linux/UNIX makefiles
#
cp generate/linux/Makefile.iasl unixtemp/compiler/Makefile
cp generate/linux/Makefile.acpisrc unixtemp/tools/acpisrc/Makefile
cp generate/linux/Makefile.acpiexec unixtemp/tools/acpiexec/Makefile
cp generate/linux/Makefile.acpihelp unixtemp/tools/acpihelp/Makefile
cp generate/linux/Makefile.acpinames unixtemp/tools/acpinames/Makefile
cp generate/linux/Makefile.acpixtract unixtemp/tools/acpixtract/Makefile
cp generate/linux/README.acpica-unix unixtemp/README

#
# Copy generic UNIX makefiles
#
mkdir -p unixtemp/generate/unix
mkdir -p unixtemp/generate/unix/acpiexec
mkdir -p unixtemp/generate/unix/acpihelp
mkdir -p unixtemp/generate/unix/acpinames
mkdir -p unixtemp/generate/unix/acpisrc
mkdir -p unixtemp/generate/unix/acpixtract
mkdir -p unixtemp/generate/unix/iasl
mkdir -p unixtemp/generate/unix/bin

cp generate/unix/readme.txt unixtemp/generate/unix/readme.txt
cp generate/unix/Makefile* unixtemp/generate/unix
cp generate/unix/acpiexec/Makefile unixtemp/generate/unix/acpiexec
cp generate/unix/acpihelp/Makefile unixtemp/generate/unix/acpihelp
cp generate/unix/acpinames/Makefile unixtemp/generate/unix/acpinames
cp generate/unix/acpisrc/Makefile unixtemp/generate/unix/acpisrc
cp generate/unix/acpixtract/Makefile unixtemp/generate/unix/acpixtract
cp generate/unix/iasl/Makefile unixtemp/generate/unix/iasl

#
# Copy Lint directory
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
mv unixtemp acpica-unix2-`date +%Y%m%d`
tar czf acpica-unix2-`date +%Y%m%d`.tar.gz acpica-unix2-`date +%Y%m%d`

#
# Move the completed package
#
mv acpica-unix2-`date +%Y%m%d`.tar.gz generate/release/current

#
# Remove the temporary directory
#
rm -rf acpica-unix2-`date +%Y%m%d`
rm -rf unixtemp


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
mkdir -p wintemp/generate/msvc9
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
# Copy project files for MS Visual Studio 2008 (VC++ 9.0)
#
cp -r generate/msvc9/*.sln wintemp/generate/msvc9/
cp -r generate/msvc9/*.vcproj wintemp/generate/msvc9/

#
# Copy generic UNIX makefiles
#
mkdir -p wintemp/generate/unix
mkdir -p wintemp/generate/unix/acpiexec
mkdir -p wintemp/generate/unix/acpihelp
mkdir -p wintemp/generate/unix/acpinames
mkdir -p wintemp/generate/unix/acpisrc
mkdir -p wintemp/generate/unix/acpixtract
mkdir -p wintemp/generate/unix/iasl
mkdir -p wintemp/generate/unix/bin

cp generate/unix/readme.txt wintemp/generate/unix/readme.txt
cp generate/unix/Makefile* wintemp/generate/unix
cp generate/unix/acpiexec/Makefile wintemp/generate/unix/acpiexec
cp generate/unix/acpihelp/Makefile wintemp/generate/unix/acpihelp
cp generate/unix/acpinames/Makefile wintemp/generate/unix/acpinames
cp generate/unix/acpisrc/Makefile wintemp/generate/unix/acpisrc
cp generate/unix/acpixtract/Makefile wintemp/generate/unix/acpixtract
cp generate/unix/iasl/Makefile wintemp/generate/unix/iasl

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
# Windows iASL and other binary tools executable package
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
cp libraries/acpihelp.exe wintemp
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
# iasl email package
# Contains: iASL executable and changes.txt file
#
# This zipfile is created with a password so that it can be safely emailed
# without interference from overzealous email scanners.
# Password is acpica
#
#******************************************************************************
echo
echo ACPICA - iASL release package
echo

#
# Make temp directory
#
mkdir wintemp

cp documents/changes.txt wintemp
cp libraries/iasl.exe wintemp
cp documents/aslcompiler.pdf wintemp
cd wintemp

$PKZIP -add -max -password=acpica ../generate/release/current/iasl-release-`date +%Y%m%d`
cd ..

#
# Remove temporary directory
#
rm -rf wintemp


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

