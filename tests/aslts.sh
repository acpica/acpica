#!/bin/bash
#
# aslts - execute ASL test suite
#
# optional parameters: <ASLTS directory path> <ACPICA source code path>
#

# Will build temporary versions of iASL and acpiexec
postfix=`date +%H%M%S`
tmp_iasl=/tmp/iasl-$postfix
tmp_acpiexec=/tmp/acpiexec-$postfix


# Setup environment and variables.
# Need a path to ASLTS and iasl,acpiexec generation dir
setup_environment() {

	aslts_dir=$1
	generation_dir=$2

	if [ -z "$generation_dir" ] ; then
		echo "missing generation directory argument"
		exit
	elif [ -z "$aslts_dir" ] ; then
		echo "missing aslts directory argument"
		exit
	elif [ ! -d "$generation_dir" ] ; then
		echo $generation_dir is not a dir
		exit
	elif [ ! -d "$aslts_dir" ] ; then
		echo $aslts_dir is not a dir
		exit
	fi

	# Variables required by ASLTS
	unset ASL
	unset acpiexec
	unset ASLTSDIR

	export ASL=$tmp_iasl
	export acpiexec=$tmp_acpiexec		
	export ASLTSDIR=$aslts_dir
	export PATH=$ASLTSDIR/bin:$PATH
}


# Generate both iASL and acpiexec from source
build_acpi_tools() {

	restore_dir=$PWD
	cd ${generation_dir}
	rm -f $tmp_iasl $tmp_acpiexec

	# Build native-width iASL compiler and acpiexec
	make clean
	make iasl
	make acpiexec

	if [ -d "bin64" ] && [ -f "bin64/iasl" ]; then
		echo "Installing 64-bit tools"
		cp bin64/iasl $tmp_iasl
		cp bin64/acpiexec $tmp_acpiexec
	elif [ -d "bin32" ] && [ -f "bin32/iasl" ]; then
		echo "Installing 32-bit tools"
		cp bin32/iasl $tmp_iasl
		cp bin32/acpiexec $tmp_acpiexec
	else
		echo "Could not find iASL/acpiexec tools"
		exit
	fi

	# Ensure that the tools are available
	if [ ! -f $tmp_iasl ] ; then
		echo "iasl compiler not found"
		exit
	elif [ ! -f $tmp_acpiexec ] ; then
		echo "acpiexec utility not found"
		exit
	fi

	cd $restore_dir
}


# Compile and run the ASLTS suite
run_aslts() {

	# Remove a previous version of the AML test code
	version=`$ASL | grep version | awk '{print $5}'`
	rm -rf $ASLTSDIR/tmp/aml/$version

	# Compile all ASL test modules
	Do 0 aslts

	# Execute the test suite
	echo ""
	echo "ASL Test Suite Started: `date`"
	start_time=$(date)
	Do 1
	echo ""
	echo "ASL Test Suite Finished: `date`"
	echo "                Started: $start_time"

	rm -f $tmp_iasl $tmp_acpiexec
}

NPARAM=$#

# Main - arguments are optional

if [ $NPARAM -eq 2 ]; then
	setup_environment $1 $2
else
	setup_environment aslts ../generate/unix
fi


build_acpi_tools
run_aslts

