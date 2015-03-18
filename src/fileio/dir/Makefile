TOP=../../..
include $(TOP)/Make.rules

ZAP = zap

PROGS =	access cdpwd chmod devrdev filetype mycd umask unlink $(ZAP)
PROGS += stat
PROGS += walk_dir
MOREPROGS = ftw8

all: $(PROGS) $(MOREPROGS)

$(PROGS):
	@ $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS)
	@ echo "Finish build $@"

ftw8: ftw8.c
	@ $(CC) $(CFLAGS) $(NAMEMAX) ftw8.c -o ftw8 $(LDFLAGS)
	@ echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)
	@ echo "Finish cleanup $(PROGS)......"
