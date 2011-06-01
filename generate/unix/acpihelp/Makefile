#
# acpihelp utility
#
include ../Makefile.config

PROG = acpihelp

#
# Flags specific to acpihelp
#
CFLAGS+= -DACPI_APPLICATION -I$(ACPICA_TOOLS)/acpihelp

OBJS = \
	ahmain.o \
	getopt.o

#
# Root rule
#
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)
	$(COPYPROG)

#
# acpihelp source
#
ahmain.o :          $(ACPICA_TOOLS)/acpihelp/ahmain.c
	$(COMPILE)

getopt.o :          $(ACPICA_COMMON)/getopt.c
	$(COMPILE)

clean : 
	rm -f $(PROG) $(PROG).exe $(OBJS)

install : 
	$(INSTALLPROG)
