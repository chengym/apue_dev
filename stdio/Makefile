ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
  MEMSTR = memstr
else
  MEMSTR =
endif

PROGS =	buf fgetsfputs getcharbug getcputc mkstemp tempfiles

all:$(PROGS) $(MEMSTR)

$(PROGS):$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)
	@ echo "Finish cleanup $(PROGS)......"
include $(ROOT)/Make.libapue.inc
