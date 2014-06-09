ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	getcputc hello ls1 mycat shell1 shell2 testerror uidgid
all: $(PROGS)

$(PROGS): $(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ $(OBJDUMP) -d $@ > $@.dump
	@ echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(TEMPFILES)
	@ echo "Finish cleanup $(PROGS)......"

include $(ROOT)/Make.libapue.inc
