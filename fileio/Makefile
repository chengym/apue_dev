ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	fileflags hole mycat seek

all: $(PROGS) setfl.o

$(PROGS): $(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(TEMPFILES) *.o file.hole
	@ echo "Finish cleanup $(PROGS)......"

include $(ROOT)/Make.libapue.inc
