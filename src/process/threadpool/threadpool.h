#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>

typedef struct _job
{
    struct _job *next;
    void *(*callback_function) (void *arg);
    void *arg;
}job;

typedef struct _threadpool
{
    /* the maxnum threads and jobs */
    int thread_num;
    int queue_max_num;

    /* job pool */
    job *head;
    job *tail;

    /* thread pool */
    pthread_t *pthreads;

    pthread_mutex_t mutex;
    pthread_cond_t queue_empty;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_not_full;

    int queue_cur_num;

    int queue_close;
    int pool_close;
}threadpool;

threadpool *threadpool_init(int thread_num, int queue_max_num);
int threadpool_add_job(threadpool *pool,
        void *(*callback_function) (void *arg), void *arg);
int threadpool_destroy(threadpool *pool);
void *threadpool_function(void *arg);
