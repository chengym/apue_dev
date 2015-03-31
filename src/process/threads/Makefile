TOP=../../..
include $(TOP)/Make.rules

BAR = barrier
EXTRALIBS=-pthread -lrt
CFLAGS += $(EXTRALIBS)

PROGS = pthread_create
PROGS += pthread_exit
PROGS += pthread_exit2
PROGS += pthread_cancel
PROGS += pthread_cleanup_push
PROGS += pthread_cond

all:$(PROGS) condvar.o maketimeout.o mutex1.o mutex2.o mutex3.o rwlock.o $(TLOCK) $(BAR)

$(PROGS):
	@ $(CC) $(CFLAGS) $@.c -o $@
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) *.o $(TLOCK) $(BAR)
	@ echo "Finish cleanup $(PROGS)......"
