TOP=..
include $(TOP)/Make.rules

PROGS =	hello getcputc ls1 mycat shell1 shell2 testerror uidgid
all: $(PROGS)

$(PROGS): $(LIBAPUE)
	 @$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS) $@.c
	 @echo "Finish build $@"

clean:
	@echo "Cleaning..."
	@rm -f $(PROGS) *.dump *.o
	@echo "Finish cleanup $(PROGS)......"
