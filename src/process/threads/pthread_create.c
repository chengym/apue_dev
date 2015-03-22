#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>

/*
 * *****************************************************************
 * chapter 11
 * threads
 *      pthread_self();
 *      pthread_equal();
 *
 *      pthread_create();
 *      pthread_exit();
 *      pthread_join();
 *      pthread_cancel();
 *      pthread_cleanup_push();
 *      pthread_cleanup_pop();
 *      pthread_detach();
 *
 * Thread Synchronization
 *      mutex:
 *          pthread_mutex_init();
 *          pthread_mutex_destroy();
 *          pthread_mutex_lock();
 *          pthread_mutex_trylock();
 *          pthread_mutex_unlock();
 *          pthread_mutex_timedlock();
 *      rw-lock:
 *          pthread_rwlock_init();
 *          pthread_rwlock_destroy();
 *          pthread_rwlock_rdlock();
 *          pthread_rwlock_wrlock();
 *          pthread_rwlock_unlock();
 *          pthread_rwlock_tryrdlock();
 *          pthread_rwlock_trywrlock();
 *          pthread_rwlock_timedrdlock();
 *          pthread_rwlock_timedwrlock();
 *      cond:
 *          pthread_cond_init();
 *          pthread_cond_destroy();
 *          pthread_cond_wait();
 *          pthread_cond_timedwait();
 *          pthread_cond_signal();
 *          pthread_cond_broadcast();
 *      spin-lock:
 *          pthread_spin_init();
 *          pthread_spin_destroy();
 *          pthread_spin_lock();
 *          pthread_spin_trylock();
 *          pthread_spin_unlock();
 *      Barrier:
 *          pthread_barrier_init();
 *          pthread_barrier_destroy();
 *          pthread_barrier_wait();
 *
 * *****************************************************************
 * chapter 12
 * attribute:
 *      pthread_attr_init();
 *      pthread_attr_destroy();
 *      pthread_attr_getdetachstate();
 *      pthread_attr_setdetachstate();
 *      pthread_attr_getstack();
 *      pthread_attr_setstack();
 *      pthread_attr_getstacksize();
 *      pthread_attr_setstacksize();
 *      pthread_attr_getguardsize();
 *      pthread_attr_setguardsize();
 *
 * sync:
 *      mutex:
 *          pthread_mutexattr_init();
 *          pthread_mutexattr_destroy();
 *          pthread_mutexattr_getpshared();
 *          pthread_mutexattr_setpshared();
 *          pthread_mutexattr_getrobust();
 *          pthread_mutexattr_setrobust();
 *          pthread_mutexattr_gettype();
 *          pthread_mutexattr_settype();
 *      rw-lock:
 *          pthread_rwlockattr_init();
 *          pthread_rwlockattr_destroy();
 *          pthread_rwlockattr_getpshared();
 *          pthread_rwlockattr_setpshared();
 *      cond:
 *          pthread_condattr_init();
 *          pthread_condattr_destroy();
 *          pthread_condattr_getpshared();
 *          pthread_condattr_setpshared();
 *          pthread_condattr_getclock();
 *          pthread_condattr_setclock();
 *      barrier:
 *          pthread_barrierattr_init();
 *          pthread_barrierattr_destroy();
 *          pthread_barrierattr_getpshared();
 *          pthread_barrierattr_setpshared();
 *          pthread_barrierattr_init();
 *
 * Reentracy:
 *      ftrylockfile();
 *      flockfile();
 *      funlockfile()
 *      getchar_unlocked();
 *      getc_runlocked();
 *      putchar_runlocked();
 *      putc_runlocked();
 *
 * private-data:
 *      pthread_key_create();
 *      pthread_key_delete();
 *      pthread_once();
 *      pthread_getspecific();
 *      pthread_setspecific();
 *
 * cancel:
 *      pthread_setcancelstate();
 *      pthread_testcancel();
 *      pthread_setcanceltype();
 *  
 *  thread-and-signal:
 *      pthread_sigmask();
 *      sigwait();
 *      pthread_kill();
 *
 *  thread-and-fork:
 *      pthread_atfork();
 *
 * */
pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long) pid,
           (unsigned long) tid, (unsigned long) tid);
}

void *thr_fn(void *arg)
{
    printids("new thread: ");
    return ((void *) 0);
}

int main(void)
{
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0)
        perror("can't create thread");
    printids("main thread:");
    sleep(1);
    exit(0);
}
