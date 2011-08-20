CC=			gcc
CFLAGS=		-g -Wall -O2
DFLAGS=	
OBJS=		ksa.o sais.o qsufsort.o
PROG=		mssac
INCLUDES=
LIBS=		-lz

.SUFFIXES:.c .o

.c.o:
		$(CC) -c $(CFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@

all:$(PROG)

mssac:$(OBJS) mssac.o
		$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) mssac.o -o $@ $(LIBS)

clean:
		rm -fr gmon.out *.o ext/*.o a.out $(PROG) *~ *.a *.dSYM session*
