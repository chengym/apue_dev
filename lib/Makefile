#
# Makefile for misc library.
#
TOP=..
include $(TOP)/Make.rules

SRCS = $(wildcard *.c .cxx)

all:$(LIBAPUE)

$(LIBAPUE):	$(SRCS)
	 @$(CC) -fPIC -shared -o $@ $(CFLAGS) $?
	 @echo "Finish build $@"

clean:
	 @rm -f *.o a.out core temp.* $(LIBAPUE)
	 @echo "Finish cleanup......"
