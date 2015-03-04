ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

CLD =

ifeq "$(PLATFORM)" "linux"
  CLD = child
endif
ifeq "$(PLATFORM)" "solaris"
  CLD = child
endif

PROGS =	critical mask read1 read2 reenter sigtstp sigusr suspend1 suspend2
MOREPROGS = systest2 tsleep2

all:$(PROGS) $(MOREPROGS) abort.o sleep1.o sleep2.o system.o $(CLD)

$(PROGS):$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
tsleep2:tsleep2.o sleep2.o
	@ $(CC) $(CFLAGS) -o tsleep2 tsleep2.o sleep2.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
systest2:systest2.o system.o
	@ $(CC) $(CFLAGS) -o systest2 systest2.o system.o $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
clean:
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o file.hole $(CLD)
	@ echo "Finish cleanup $(PROGS)......"
include $(ROOT)/Make.libapue.inc
