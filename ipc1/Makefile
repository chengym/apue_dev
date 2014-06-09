ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	add2 add2stdio devzero myuclc pipe1 pipe2 pipe4 popen1 popen2 tshm

all: $(PROGS) popen.o slock.o tellwait.o

$(PROGS): $(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

slock.o: slock.c slock.h

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(TEMPFILES) *.o
	@ echo "Finish cleanup $(PROGS)......"

include $(ROOT)/Make.libapue.inc
