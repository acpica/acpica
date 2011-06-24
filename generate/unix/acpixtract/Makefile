#
# acpixtract - extract binary ACPI tables from acpidump text output
#

#
# Note: This makefile is intended to be used from within the native
# ACPICA directory structure, from under generate/unix. It specifically
# places all object files in a generate/unix subdirectory, not within
# the various ACPICA source directories. This prevents collisions
# between different compilations of the same source file with different
# compile options, and prevents pollution of the source code.
#
include ../Makefile.config
PROG = acpixtract

#
# Flags specific to acpixtract
#
CFLAGS+= \
    -DACPI_XTRACT_APP \

OBJS = \
    acpixtract.o \
    axmain.o \
    getopt.o

#
# Root rule
#
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)
	$(COPYPROG)

#
# acpixtract source
#
acpixtract.o :          $(ACPICA_TOOLS)/acpixtract/acpixtract.c
	$(COMPILE)

axmain.o :              $(ACPICA_TOOLS)/acpixtract/axmain.c
	$(COMPILE)

#
# ACPICA core source - common
#
getopt.o :          $(ACPICA_COMMON)/getopt.c
	$(COMPILE)


clean :
	rm -f $(PROG) $(PROG).exe $(OBJS)

install :
	$(INSTALLPROG)
