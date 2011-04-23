CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer
CXXFLAGS=	$(CFLAGS)
OBJS=		../benchmark/benchmark.o ../runit/runlib.o test.o
DFLAGS=
INCLUDES=	-I../benchmark -I../runit
LIBS=		

.SUFFIXES:.c .o

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

.cc.o:
		$(CXX) -c $(INCLUDES) $(CXXFLAGS) $(DFLAGS) $< -o $@

all:test

test:$(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

test2:../runit/runlib.o ../benchmark/benchmark.o test2.cc
		$(CXX) $(CXXFLAGS) $(INCLUDES) -std=c++0x -o $@ test2.cc ../runit/runlib.o ../benchmark/benchmark.o $(LIBS)

cleanlocal:
		rm -f *.o a.out *~ test

clean:cleanlocal

