TOP =.
include $(TOP)/Make.rules

DIRS = lib \
	   intro \
	   src/fileio/fileio \
	   src/fileio/filedir \
	   src/process/proc \
	   src/process/threadctl \
	   src/process/threads \
	   src/stdio \
	   src/termios \
	   src/singal/signals

#sockets advio daemons datafiles db environ         \
#	   fileio filedir ipc1 ipc2 proc pty relation signals standards \
#	   stdio termios threadctl threads printer exercises

all:
	@ for i in $(DIRS); do $(MAKE) -C $$i; done
	@echo "Finish building $@..."

clean:
	@ echo "Cleaning $(DIRS)..."
	@ for i in $(DIRS); do  $(MAKE) -C $$i clean; done
