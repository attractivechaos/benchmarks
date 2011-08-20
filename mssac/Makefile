CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -O2
CXXFLAGS=	$(CFLAGS)
DFLAGS=	
OBJS=		ksa.o sais.o divsufsort.o qsufsort.o ssort.o dc3.o
PROG=		mssac
INCLUDES=
LIBS=		-lz

.SUFFIXES:.c .o

.c.o:
		$(CC) -c $(CFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@
.cc.o:
		$(CXX) -c $(CXXFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@

all:$(PROG)

mssac:$(OBJS) mssac.o
		$(CXX) $(CFLAGS) $(DFLAGS) $(OBJS) mssac.o -o $@ $(LIBS)

clean:
		rm -fr gmon.out *.o ext/*.o a.out $(PROG) *~ *.a *.dSYM session*
