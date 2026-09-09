#!/bin/sh
#
# externals - check the external control method counters of the disassembler
#
# While it disassembles a table, the disassembler counts the external control
# methods that it finds, and the methods that it resolves. It prints a warning
# when the two counts differ. Both counters must hold more than 255 methods.
#
# Each test case builds a table that refers to a given number of control
# methods, disassembles it, and reads the two counts back from the warning.
# The counts near 256 are the important ones. A counter that is one byte wide
# truncates them, and the disassembler then prints a wrong count, or prints
# no warning at all.
#

ASL_COMPILER=${ASL:-iasl}

echo "Using $ASL_COMPILER"

tmpdir=`mktemp -d` || exit 1
trap 'rm -rf "$tmpdir"' EXIT

asl=$tmpdir/externals.asl
aml=$tmpdir/externals.aml
dsl=$tmpdir/externals.dsl

status=0

#
# Write a table that invokes COUNT control methods.
#
# KIND "declared" adds an External declaration for each method. The compiler
# puts an External opcode into the AML, therefore the disassembler resolves
# every method.
#
# KIND "undeclared" omits the declarations. The AML then holds no External
# opcode, therefore the disassembler resolves none of the methods. The missing
# declarations are compilation errors, which is why the compiler needs -f.
#
write_table()
{
	count=$1
	kind=$2
	i=0

	echo 'DefinitionBlock ("", "DSDT", 2, "Intel", "EXTERNAL", 1)'
	echo '{'

	if [ "$kind" = declared ] ; then
		while [ $i -lt $count ] ; do
			printf '    External (\\M%03X, MethodObj, IntObj, {IntObj})\n' $i
			i=$((i + 1))
		done
	fi

	echo '    Method (MAIN, 0)'
	echo '    {'

	i=0
	while [ $i -lt $count ] ; do
		printf '        \\M%03X (One)\n' $i
		i=$((i + 1))
	done

	echo '    }'
	echo '}'
}

#
# Read the three counts out of the disassembler warning: the methods found,
# the methods resolved, and the methods left unresolved. Print nothing when
# the disassembler prints no warning.
#
warning_counts()
{
	sed -n '/iASL Warning: There w/,/unresolved)/p' "$1" | tr -cs '0-9' ' '
}

#
# Disassemble a table that refers to COUNT methods of the given KIND, and
# compare the counts in the warning against EXPECTED. An empty EXPECTED means
# that the disassembler must print no warning.
#
run_case()
{
	count=$1
	kind=$2
	expected=$3

	rm -f "$asl" "$aml" "$dsl"
	write_table "$count" "$kind" > "$asl"

	$ASL_COMPILER -f -p "$tmpdir/externals" "$asl" > /dev/null 2>&1
	$ASL_COMPILER -d "$aml" > /dev/null 2>&1

	if [ ! -f "$dsl" ] ; then
		printf "External methods %s %s FAIL (no disassembly)\n" "$count" "$kind"
		status=1
		return
	fi

	# The word splitting removes the padding that tr leaves behind.
	set -- `warning_counts "$dsl"`
	found="$*"

	if [ "$found" = "$expected" ] ; then
		printf "External methods %s %s PASS\n" "$count" "$kind"
	else
		printf "External methods %s %s FAIL (expected \"%s\", found \"%s\")\n" \
			"$count" "$kind" "$expected" "$found"
		status=1
	fi
}

# No external methods at all, so there is nothing to warn about.

run_case 0 undeclared ""

# One unresolved method. The warning uses the singular wording.

run_case 1 undeclared "1 0 1"

# The last count that fits in one byte, and the first count that does not.

run_case 255 undeclared "255 0 255"
run_case 256 undeclared "256 0 256"

# Every method is resolved, so there is nothing to warn about. A truncated
# count differs from the resolved count and makes the disassembler print a
# warning with a huge unresolved count.

run_case 300 declared ""

exit $status
