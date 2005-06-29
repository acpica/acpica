 

PROG=	acpisrc
SRCS=	ascase.c asconvrt.c asfile.c asmain.c asremove.c asutils.c osunixdir.c \
        ../../common/getopt.c

CFLAGS+= -Wall -O2 -D_LINUX -Wstrict-prototypes -I../../include 


aslmain : $(patsubst %.c,%.o, $(SRCS))
	$(CC) $(LDFLAGS) $(patsubst %.c,%.o, $(SRCS)) -o $(PROG)

CLEANFILES= $(PROG)

clean : 
	rm -f $(CLEANFILES) $(patsubst %.c,%.o, $(SRCS))

