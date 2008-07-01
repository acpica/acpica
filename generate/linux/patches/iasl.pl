#! /usr/bin/perl
#
# Obtain and generate ACPICA iASL compiler from source
#

# Get the very latest version of ACPICA (source, headers, makefile)

system("echo Getting latest version of ACPICA");
system("perl get-acpi.pl");

# Flatten the components directory

system("rm -rf Acpi/source/components/CVS");
system("mv Acpi/source/components/* Acpi/source");

# Create the iASL compiler

system("echo Generate acpiexec utility from source");
system("sh iasl.sh");
