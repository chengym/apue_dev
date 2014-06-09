ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	orphan3

all:$(PROGS)

$(PROGS):$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
clean:
	@ rm -f $(PROGS) $(TEMPFILES) *.o
	@ echo "Finish cleanup $(PROGS)......"
include $(ROOT)/Make.libapue.inc
