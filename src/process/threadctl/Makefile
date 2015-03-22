TOP=../../..
include $(TOP)/Make.rules

CFLAGS += -pthread

TOUT = timeout.o

PROGS =	atfork suspend

all:$(PROGS) detach.o getenv1.o getenv2.o getenv3.o $(TOUT)

$(PROGS):
	@ $(CC) $(CFLAGS) $@.c -o $@
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) *.o
	@ echo "Finish cleanup $(PROGS)......"
