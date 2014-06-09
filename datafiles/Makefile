ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	strftime

all:	$(PROGS) getpwnam.o

$(PROGS):	$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(TEMPFILES) *.o
	@ echo "Finish cleanup $(PROGS)......"

include $(ROOT)/Make.libapue.inc
