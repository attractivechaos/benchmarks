CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer
OBJS=		test.o
DFLAGS=
#INCLUDES=
#LIBS=		
INCLUDES=	-I$(HOME)/opt/include
LIBS=		$(HOME)/opt/lib/libre2.a

.SUFFIXES:.c .o .cc

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

.cc.o:
		$(CXX) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

all:test

test:$(OBJS)
		$(CXX) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

cleanlocal:
		rm -f *.o a.out *~ test

clean:cleanlocal
