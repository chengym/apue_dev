ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
  EXTRALIBS=-lrt
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS=-lrt
endif

PROGS =	deadlock mandatory mcopy2 nonblockw rot13a
MOREPROGS = rot13c2

all:	$(PROGS) $(MOREPROGS) lockfile.o

rot13c2.c:	rot13c2.c.in $(LIBAPUE)
	./fixup.awk rot13a.c >xlate
	sed '/same/q' rot13c2.c.in >rot13c2.c
	cat xlate >>rot13c2.c
	sed '1,/same/d' rot13c2.c.in >>rot13c2.c

$(PROGS):	$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o xlate rot13c2.c
	@ echo "Finish cleanup $(PROGS)......"

include $(ROOT)/Make.libapue.inc
