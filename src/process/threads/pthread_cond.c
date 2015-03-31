#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *);
void *thread2(void *);

int i = 1;

int main(void)
{
    int ret;
    pthread_t t_a;
    pthread_t t_b;

    ret = pthread_create(&t_a, NULL, thread1, NULL);
    assert(0 == ret);
    ret = pthread_create(&t_b, NULL, thread2, NULL);
    assert(0 == ret);

    pthread_join(t_a, NULL);
    pthread_join(t_b, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    exit(0);
}

void *thread1(void *junk)
{
    for (i = 1; i <= 6; i++) {
        /* get mutex lock */
        pthread_mutex_lock(&mutex);

        printf("thread1: lock %d\n", __LINE__);
        if (i % 3 == 0) {
            printf("thread1:signal 1  %d\n", __LINE__);
            /* send cond means ready */
            pthread_cond_signal(&cond);
            printf("thread1:signal 2  %d\n", __LINE__);
            sleep(1);
        }
        /* wakeup thread2 */
        pthread_mutex_unlock(&mutex);
        printf("thread1: unlock %d\n\n", __LINE__);
        sleep(1);
    }
}

void *thread2(void *junk)
{
    while (i < 6) {
        /* get mutex lock */
        pthread_mutex_lock(&mutex);

        printf("thread2: lock %d\n", __LINE__);
        if (i % 3 != 0) {
            printf("thread2: wait 1  %d\n", __LINE__);
            /* release mutex and sleep for cond */
            pthread_cond_wait(&cond, &mutex);
            printf("thread2: wait 2  %d\n", __LINE__);
        }
        /* wakeup thread1 */
        pthread_mutex_unlock(&mutex);
        printf("thread2: unlock %d\n\n", __LINE__);
        sleep(1);
    }
}
