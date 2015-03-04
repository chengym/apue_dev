ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lsocket -lnsl
endif

PROGS = ruptime ruptimed ruptimed-fd ruptimed-dg
MOREPROGS = findsvc ruptime-dg

all:	$(PROGS) $(MOREPROGS) clconn.o clconn2.o initsrv1.o initsrv2.o 

$(PROGS):	$(LIBAPUE)

ruptime:	ruptime.o clconn2.o
	@ $(CC) $(CFLAGS) -o ruptime ruptime.o clconn2.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
ruptimed:	ruptimed.o initsrv2.o
	@ $(CC) $(CFLAGS) -o ruptimed ruptimed.o initsrv2.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
ruptimed-fd:	ruptimed-fd.o initsrv2.o
	@ $(CC) $(CFLAGS) -o ruptimed-fd ruptimed-fd.o initsrv2.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

ruptimed-dg:	ruptimed-dg.o initsrv2.o
	@ $(CC) $(CFLAGS) -o ruptimed-dg ruptimed-dg.o initsrv2.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
clean:
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o
	@ echo "Finish cleanup $(PROGS)......"
include $(ROOT)/Make.libapue.inc
