TOP=../../..
include $(TOP)/Make.rules

BAR = barrier
EXTRALIBS=-pthread -lrt
CFLAGS += $(EXTRALIBS)

PROGS = badexit2 cleanup exitstatus threadid

all:$(PROGS) condvar.o maketimeout.o mutex1.o mutex2.o mutex3.o rwlock.o $(TLOCK) $(BAR)

$(PROGS):
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) *.o $(TLOCK) $(BAR)
	@ echo "Finish cleanup $(PROGS)......"
