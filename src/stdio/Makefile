TOP=../..
include $(TOP)/Make.rules

MEMSTR = memstr

PROGS =	buf fgetsfputs getcharbug getcputc mkstemp tempfiles

all:$(PROGS) $(MEMSTR)

$(PROGS):$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)
	@ echo "Finish cleanup $(PROGS)......"
