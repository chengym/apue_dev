ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	csize settty t_getpass t_isatty t_raw t_ttyname winch

all:$(PROGS) ctermid.o getpass.o isatty.o ttyname.o

$(PROGS):$(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"
clean:
	@ rm -f $(PROGS) $(TEMPFILES) *.o
	@ echo "Finish cleanup $(PROGS)......"
include $(ROOT)/Make.libapue.inc
