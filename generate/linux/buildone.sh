#
# buildone - Build one ACPI utility
# usage:
#   buildone <UtilityName> [clean | install]
#
mkdir -p bin

#
# Setup directories
#
if [ $1 = iasl ]; then
    BUILD_SOURCE=../../source/compiler
    START_DIR=../..
else
    BUILD_SOURCE=../../source/tools/$1
    START_DIR=../../..
fi

#
# Copy the makefile to the target directory
#
cp Makefile.$1 $BUILD_SOURCE/Makefile

#
# Implementation of "buildall clean" and "buildall install"
#
if [ "$2" != "" ]; then 
    if [ $2 = clean ]; then

        # cleanup
        
        echo "*** clean $1"
        cd $BUILD_SOURCE
        make ACPICA_COMPONENTS="/components" clean
        rm Makefile
        exit 0
    elif [ $2 = install ]; then

        # intall program
        
        echo "*** install $1"
        cd $BUILD_SOURCE
        make ACPICA_COMPONENTS="/components" install
        exit 0
    fi
fi

#
# Build the utility
#
rm -f bin/$1
cd $BUILD_SOURCE
echo "*** make $1 (from $BUILD_SOURCE)"

make ACPICA_COMPONENTS="/components"
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "*** make $1 FAILED $STATUS"
else
    cp $1.exe $START_DIR/generate/linux/bin
fi

cd $START_DIR/generate/linux
echo "*** completed $1"
exit $STATUS

