#! /usr/bin/perl
#
# Obtain and generate ACPICA acpiexec utility from source
#

# Get the very latest version of ACPICA (source, headers, makefile)

system("echo Getting latest version of ACPICA");
system("perl get-acpi.pl");

# Flatten the components directory
# *** WHY?

system("rm -rf Acpi/source/components/CVS");
system("mv Acpi/source/components/* Acpi/source");

# Create the acpiexec utility

system("echo Generate acpiexec utility from source");
system("sh acpiexec.sh");
