#
# buildall - Build all ACPI utilities
# usage:
#   buildall [clean | install]
#
BUILD_COUNT=0
STATUS=0

#
# Common exit. Assumes $STATUS has been set.
#
exit_build()
{
    if [ $STATUS -ne 0 ]; then
        echo "*** build $1 FAILED $STATUS"
    fi
    
    echo "*** $BUILD_COUNT successful builds"
    exit $STATUS
}

#
# Build one utility
#
do_build()
{
    ./buildone.sh $1 $2
    STATUS=$?
    if [ $STATUS -ne 0 ]; then
        exit_build $1
    fi
    
    BUILD_COUNT=`expr $BUILD_COUNT + 1`    
}

#
# Build all utilities
#
do_build iasl $1
do_build acpiexec $1
do_build acpinames $1
do_build acpixtract $1
do_build acpihelp $1
do_build acpisrc $1
do_build acpibin $1

exit_build
