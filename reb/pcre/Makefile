CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer
OBJS=		
DFLAGS=
#INCLUDES=
#LIBS=		
INCLUDES=	-I$(HOME)/opt/include
LIBS=		$(HOME)/opt/lib/libpcre*.a

.SUFFIXES:.c .o .cc

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

.cc.o:
		$(CXX) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

all:test-posix test-cpp

test-posix:test-posix.o
		$(CC) $(CFLAGS) -o $@ test-posix.o $(LIBS)

test-cpp:test-cpp.o
		$(CXX) $(CFLAGS) -o $@ test-cpp.o $(LIBS)

cleanlocal:
		rm -f *.o a.out *~ test test-posix test-cpp

clean:cleanlocal
