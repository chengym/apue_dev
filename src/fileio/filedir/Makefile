TOP=../../..
include $(TOP)/Make.rules

ZAP = zap

PROGS =	access cdpwd changemod devrdev filetype mycd umask unlink $(ZAP)
MOREPROGS = ftw8

all: $(PROGS) $(MOREPROGS)

$(PROGS): $(LIBAPUE)
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

ftw8: ftw8.c $(LIBAPUE)
	@ $(CC) $(CFLAGS) $(NAMEMAX) ftw8.c -o ftw8 $(LDFLAGS) $(LDLIBS)
	@ echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)
	@ echo "Finish cleanup $(PROGS)......"
