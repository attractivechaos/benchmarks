CC=			gcc
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer
OBJS=		test-posix.o
DFLAGS=
#INCLUDES=
#LIBS=		
INCLUDES=	-I$(HOME)/opt/include
LIBS=		$(HOME)/opt/lib/libonig.a

.SUFFIXES:.c .o

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

all:test-posix

test-posix:$(OBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

cleanlocal:
		rm -f *.o a.out *~ test test-posix

clean:cleanlocal
