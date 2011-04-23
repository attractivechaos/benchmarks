CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -O2 -fomit-frame-pointer #-m64
CXXFLAGS=	$(CFLAGS)
DFLAGS=		
OBJS=		
LIBS=		
SUBDIRS=	regex regex-old regexp9 tre trex re2 pcre onig boost \
			xpressive tcl glib

.SUFFIXES:.c .o .cc

.c.o:
		$(CC) -c $(CFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@
.cc.o:
		$(CXX) -c $(CXXFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@

all:all-recur

lib-recur all-recur clean-recur cleanlocal-recur install-recur:
		@target=`echo $@ | sed s/-recur//`; \
		wdir=`pwd`; \
		list='$(SUBDIRS)'; for subdir in $$list; do \
			cd $$subdir; \
			$(MAKE) CC="$(CC)" CXX="$(CXX)" DFLAGS="$(DFLAGS)" CFLAGS="$(CFLAGS)" \
				$$target || exit 1; \
			cd $$wdir; \
		done;

lib:

cleanlocal:
		rm -f gmon.out *.o stdhash/*.o a.out *~ *.a

clean:cleanlocal-recur
	find . -name "*~"|xargs rm