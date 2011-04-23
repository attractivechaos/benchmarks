CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer
OBJS=		test.o
DFLAGS=
#INCLUDES=
#LIBS=		
INCLUDES=	-I/opt/local/include
LIBS=		/opt/local/lib/libboost_regex.a

.SUFFIXES:.c .o .cc

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

.cc.o:
		$(CXX) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

all:test test-iostream

test:test.o
		$(CXX) $(CFLAGS) -o $@ test.o $(LIBS)

test-iostream:test-iostream.o
		$(CXX) $(CFLAGS) -o $@ test-iostream.o $(LIBS)

cleanlocal:
		rm -f *.o a.out *~ test test-iostream

clean:cleanlocal
