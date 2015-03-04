TOP=../../..
include $(TOP)/Make.rules

PROGS =	fileflags hole mycat seek

all: $(PROGS) setfl.o

$(PROGS): $(LIBAPUE)
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS) $@.c
	@echo "Finish build $@"

clean:
	@ echo "Cleaning..."
	@ rm -f $(PROGS) *.o file.hole
	@ echo "Finish cleanup $(PROGS)......"
