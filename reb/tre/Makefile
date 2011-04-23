CC=			gcc
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer
OBJS=		test.o
DFLAGS=
#INCLUDES=
#LIBS=		
INCLUDES=	-I$(HOME)/opt/include
LIBS=		-L$(HOME)/opt/lib -ltre

.SUFFIXES:.c .o

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $(DFLAGS) $< -o $@

all:test

test:$(OBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

cleanlocal:
		rm -f *.o a.out *~ test

clean:cleanlocal
