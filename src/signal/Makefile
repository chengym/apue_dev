TOP=../..
include $(TOP)/Make.rules

CLD = child

PROGS =	critical mask read1 read2 reenter sigtstp sigusr suspend1 suspend2 sleep1
PROGS += sigprocmask
PROGS += 10.6
MOREPROGS = systest2 tsleep2

all:$(PROGS) $(MOREPROGS) abort.o sleep1.o sleep2.o system.o $(CLD)

$(PROGS):
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS)
	@ echo "Finish build $@"
tsleep2:tsleep2.o sleep2.o
	@ $(CC) $(CFLAGS) -o tsleep2 tsleep2.o sleep2.o $(LDFLAGS)
	@ echo "Finish build $@"
systest2:systest2.o system.o
	@ $(CC) $(CFLAGS) -o systest2 systest2.o system.o $(LDFLAGS)
	@ echo "Finish build $@"
clean:
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o file.hole $(CLD)
	@ echo "Finish cleanup $(PROGS)......"
