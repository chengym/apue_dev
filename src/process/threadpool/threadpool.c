#include "threadpool.h"
#include <assert.h>

threadpool *threadpool_init(int thread_num, int queue_max_num)
{
    int i;
    threadpool *pool;

    pool = malloc(sizeof(threadpool));
    if (!pool) {
        printf("failed to malloc threadpool!\n");
        goto end;
    }
    pool->thread_num = thread_num;
    pool->queue_max_num = queue_max_num;
    pool->queue_cur_num = 0;
    pool->head = NULL;
    pool->tail = NULL;

    /* init mutex/cond */
    if (pthread_mutex_init(&(pool->mutex), NULL)) {
        printf("failed to init mutex!\n");
        goto end;
    }
    if (pthread_cond_init(&(pool->queue_empty), NULL)) {
        printf("failed to init queue_empty!\n");
        goto end;
    }
    if (pthread_cond_init(&(pool->queue_not_empty), NULL)) {
        printf("failed to init queue_not_empty!\n");
        goto end;
    }
    if (pthread_cond_init(&(pool->queue_not_full), NULL)) {
        printf("failed to init queue_not_full!\n");
        goto end;
    }
    pool->pthreads = malloc(sizeof(pthread_t) * thread_num);
    if (NULL == pool->pthreads) {
        printf("failed to malloc pthreads!\n");
        goto end;
    }

    /* open for queue and thread pool */
    pool->queue_close = 0;
    pool->pool_close = 0;

    /* init threads */
    for (i = 0; i < pool->thread_num; ++i) {
        pthread_create(&(pool->pthreads[i]), NULL, threadpool_function,
                       (void*)pool);
    }

    return pool;
end:
    return NULL;
}

int threadpool_add_job(threadpool *pool,
                       void *(*callback_function) (void *arg), void *arg)
{
    job *pjob;

    assert(pool != NULL);
    assert(callback_function != NULL);
    assert(arg != NULL);

    pthread_mutex_lock(&(pool->mutex));

    /* wait cond when queuee is full */
    while ((pool->queue_cur_num == pool->queue_max_num)
           && !(pool->queue_close || pool->pool_close)) {
        pthread_cond_wait(&(pool->queue_not_full), &(pool->mutex));
    }

    /* return when pthreadpool or queue closed */
    if (pool->queue_close || pool->pool_close) {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }

    pjob = (job *) malloc(sizeof(job));
    if (NULL == pjob) {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }

    pjob->callback_function = callback_function;
    pjob->arg = arg;

    pjob->next = NULL;
    if (pool->head == NULL) {
        pool->head = pool->tail = pjob;
        /* wakeup thread but thread can't not run right now */
        pthread_cond_broadcast(&(pool->queue_not_empty));
    } else {
        pool->tail->next = pjob;
        pool->tail = pjob;
    }
    pool->queue_cur_num++;

    pthread_mutex_unlock(&(pool->mutex));
    return 0;
}

void *threadpool_function(void *arg)
{
    threadpool *pool = (threadpool *) arg;
    job *pjob = NULL;

    while (1) {
        pthread_mutex_lock(&(pool->mutex));

        /* it will sleep on cond queue_not_empty when no job to do */
        while ((pool->queue_cur_num == 0) && !pool->pool_close) {
            pthread_cond_wait(&(pool->queue_not_empty), &(pool->mutex));
        }

        /* guarantee thread pool not closed */
        if (pool->pool_close) {
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }

        /* decrease queue_cur_num */
        pool->queue_cur_num--;

        pjob = pool->head;
        if (pool->queue_cur_num == 0) {
            pool->head = pool->tail = NULL;
        } else {
            pool->head = pjob->next;
        }

        if (pool->queue_cur_num == 0) {
            /* 
             * wakeup the thread sleep on cond queue_empty,
             * it will wakeup the-main thread in this case
             * */
            pthread_cond_signal(&(pool->queue_empty));
        }
        if (pool->queue_cur_num == pool->queue_max_num - 1) {
            /* wakeup all the threadpool_add_job threads */
            pthread_cond_broadcast(&(pool->queue_not_full));
        }

        pthread_mutex_unlock(&(pool->mutex));

        /* callback and destory the job */
        (*(pjob->callback_function)) (pjob->arg);
        free(pjob);
        pjob = NULL;
    }
}

int threadpool_destroy(threadpool *pool)
{
    int i;
    job *p;

    assert(pool != NULL);

    pthread_mutex_lock(&(pool->mutex));

    if (pool->queue_close || pool->pool_close) {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }

    pool->queue_close = 1;
    while (pool->queue_cur_num != 0) {
        pthread_cond_wait(&(pool->queue_empty), &(pool->mutex));
    }

    pool->pool_close = 1;
    pthread_mutex_unlock(&(pool->mutex));
    pthread_cond_broadcast(&(pool->queue_not_empty));
    pthread_cond_broadcast(&(pool->queue_not_full));

    /* destory thread */
    for (i = 0; i < pool->thread_num; ++i) {
        pthread_join(pool->pthreads[i], NULL);
    }

    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->queue_empty));
    pthread_cond_destroy(&(pool->queue_not_empty));
    pthread_cond_destroy(&(pool->queue_not_full));

    /* destory job and threadpool */
    free(pool->pthreads);
    while (pool->head != NULL) {
        p = pool->head;
        pool->head = p->next;
        free(p);
    }

    free(pool);
    return 0;
}
