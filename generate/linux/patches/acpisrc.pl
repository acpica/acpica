#! /usr/bin/perl
#
# Obtain and generate ACPICA acpisrc utility from source
#

# Get the very latest version of ACPICA (source, headers, makefile)

system("echo Getting latest version of ACPICA");
system("perl get-acpi.pl");

# Create the acpiexec utility

system("echo Generate acpisrc utility from source");
system("sh acpisrc.sh");
