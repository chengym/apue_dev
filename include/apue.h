#ifndef	_APUE_H
#define	_APUE_H

#define _POSIX_C_SOURCE 200809L

#if defined(SOLARIS)            /* Solaris 10 */
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 700
#endif

#include <sys/types.h>          /* some systems still require this */
#include <sys/stat.h>
#include <sys/termios.h>        /* for winsize */
#if defined(MACOS) || !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define	MAXLINE	4096            /* max line length */

/* Default file access permissions for new files. */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
/* Default permissions for new directories. */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int);      /* for signal handlers */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

/*
 * Prototypes for our own functions.
 */
char *path_alloc(size_t *);     /* {Prog pathalloc} */
long open_max(void);            /* {Prog openmax} */

int set_cloexec(int);           /* {Prog setfd} */
void clr_fl(int, int);
void set_fl(int, int);          /* {Prog setfl} */

void pr_exit(int);              /* {Prog prexit} */

void pr_mask(const char *);     /* {Prog prmask} */
Sigfunc *signal_intr(int, Sigfunc *);   /* {Prog signal_intr_function} */

void daemonize(const char *);   /* {Prog daemoninit} */

void sleep_us(unsigned int);    /* {Ex sleepus} */
ssize_t readn(int, void *, size_t);     /* {Prog readn_writen} */
ssize_t writen(int, const void *, size_t);      /* {Prog readn_writen} */

int fd_pipe(int *);             /* {Prog sock_fdpipe} */
int recv_fd(int, ssize_t(*func) (int, const void *, size_t));   /* {Prog recvfd_sockets} */
int send_fd(int, int);          /* {Prog sendfd_sockets} */
int send_err(int, int, const char *);   /* {Prog senderr} */
int serv_listen(const char *);  /* {Prog servlisten_sockets} */
int serv_accept(int, uid_t *);  /* {Prog servaccept_sockets} */
int cli_conn(const char *);     /* {Prog cliconn_sockets} */
int buf_args(char *, int (*func) (int, char **));       /* {Prog bufargs} */

int tty_cbreak(int);            /* {Prog raw} */
int tty_raw(int);               /* {Prog raw} */
int tty_reset(int);             /* {Prog raw} */
void tty_atexit(void);          /* {Prog raw} */
struct termios *tty_termios(void);      /* {Prog raw} */

int ptym_open(char *, int);     /* {Prog ptyopen} */
int ptys_open(char *);          /* {Prog ptyopen} */
#ifdef	TIOCGWINSZ
pid_t pty_fork(int *, char *, int, const struct termios *, const struct winsize *);     /* {Prog ptyfork} */
#endif

int lock_reg(int, int, int, off_t, int, off_t); /* {Prog lockreg} */

#define	read_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define	readw_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define	write_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define	writew_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define	un_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

pid_t lock_test(int, int, off_t, int, off_t);   /* {Prog locktest} */

#define	is_read_lockable(fd, offset, whence, len) \
			(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define	is_write_lockable(fd, offset, whence, len) \
			(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

void err_msg(const char *, ...);
void err_dump(const char *, ...);
void err_quit(const char *, ...);
void err_cont(int, const char *, ...);
void err_exit(int, const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

void log_msg(const char *, ...);        /* {App misc_source} */
void log_open(const char *, int, int);
void log_quit(const char *, ...) __attribute__ ((noreturn));
void log_ret(const char *, ...);
void log_sys(const char *, ...) __attribute__ ((noreturn));
void log_exit(int, const char *, ...) __attribute__ ((noreturn));

void TELL_WAIT(void);           /* parent/child from {Sec race_conditions} */
void TELL_PARENT(pid_t);
void TELL_CHILD(pid_t);
void WAIT_PARENT(void);
void WAIT_CHILD(void);

#define APUE_LOG_ENABLE
#define APUE_ASSERT_ENABLE

#ifdef APUE_LOG_ENABLE
#define APUE_DEBUG_E(format, ...) printf(__FILE__":%s(%d):" format, __func__, __LINE__, ##__VA_ARGS__)
#else
#define APUE_DEBUG_E printf
#endif

#define apue_print(format, ...) printf(format, ##__VA_ARGS__)

#ifdef APUE_ASSERT_ENABLE
#define APUE_ASSERT(x) \
   if (x) { \
       printf("###AUTO_REPORT: FAIL at %s(%d), "#x" = 0x%08x\n", __FILE__, __LINE__, (unsigned int)x);\
       while(1);\
   }
#else
#define APUE_ASSERT(x)
#endif

#endif /* _APUE_H */
