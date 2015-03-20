TOP=../../..
include $(TOP)/Make.rules

BAR = barrier
EXTRALIBS=-pthread -lrt
CFLAGS += $(EXTRALIBS)

PROGS = badexit2 cleanup exitstatus threadid
PROGS += pthread_create
PROGS += pthread_cancel
PROGS += pthread_cleanup_push

all:$(PROGS) condvar.o maketimeout.o mutex1.o mutex2.o mutex3.o rwlock.o $(TLOCK) $(BAR)

$(PROGS):
	@ $(CC) $(CFLAGS) $@.c -o $@
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) *.o $(TLOCK) $(BAR)
	@ echo "Finish cleanup $(PROGS)......"
