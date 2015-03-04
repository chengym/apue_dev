ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TOUT =
ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS = -pthread
  TOUT = timeout.o
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lpthread
  TOUT = timeout.o
endif

PROGS =	atfork suspend

all:$(PROGS) detach.o getenv1.o getenv2.o getenv3.o $(TOUT)

$(PROGS): $(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ rm -f $(PROGS) $(TEMPFILES) *.o
	@ echo "Finish cleanup $(PROGS)......"

include $(ROOT)/Make.libapue.inc
