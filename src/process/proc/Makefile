TOP=../../..
include $(TOP)/Make.rules

ACCT=pracct
ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE

PROGS =	echoall exec1 exec2 fork1 fork2 nice pruids tellwait1 tellwait2 test1 times1 vfork1 wait1
MOREPROGS = systest1 systest3

all:$(PROGS) $(MOREPROGS) system.o $(ACCT)

$(PROGS):$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

systest1:system.o systest1.o
	@ $(CC) $(CFLAGS) -o systest1 systest1.o system.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

systest3:system.o systest3.o
	@ $(CC) $(CFLAGS) -o systest3 systest3.o system.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

pracct:	pracct.c
	@ $(CC) $(CFLAGS) $(ACCTFLAGS) -o pracct pracct.c $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ACCT)
	@ echo "Finish cleanup $(PROGS)......"
