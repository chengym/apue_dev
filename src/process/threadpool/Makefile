TOP=../../..
include $(TOP)/Make.rules

CFLAGS += -pthread

PROGS = threadpool

all:$(PROGS)

$(PROGS):
	@ $(CC) $(CFLAGS)  threadpool.c main.c -o $@
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) *.o
	@ echo "Finish cleanup $(PROGS)......"
