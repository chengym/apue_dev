#include <stdlib.h>
#include <pthread.h>

#include "list.h"

/*=============================================================*/
typedef struct _job
{
    list_head node;

    pthread_t j_id;
}job;

typedef struct _queue
{
    list_head head;
    unsigned int num;

    pthread_rwlock_t q_lock;
}queue;

int queue_init(queue *qp);
void job_insert(queue *qp, job *jp);
void job_append(queue *qp, job *jp);
void job_remove(queue *qp, job *jp);
job *job_find(queue *qp, pthread_t id);

/*=============================================================*/

/*
 * Initialize a queue.
 */
int queue_init(queue *qp)
{
    int err;

    INIT_LIST_HEAD(&(qp->head));

    err = pthread_rwlock_init(&qp->q_lock, NULL);
    if (err != 0) {
        perror("pthread_rwlock_init");
    }

    return 0;
}

/*
 * Insert a job at the head of the queue.
 */
void job_insert(queue *qp, job *jp)
{
    /* get wrlock, blocked by the existed rdlock but block the comming rdlock */
    pthread_rwlock_wrlock(&qp->q_lock);

    list_add(&(jp->node), &(qp->head));

    /* release wrlock, this will wakeup the rdlock or wrlock */
    pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Append a job on the tail of the queue.
 */
void job_append(queue *qp, job *jp)
{
    /* get wrlock, blocked by the existed rdlock but block the comming rdlock */
    pthread_rwlock_wrlock(&qp->q_lock);

    list_add_tail(&(jp->node), &(qp->head));

    /* release wrlock, this will wakeup the rdlock or wrlock */
    pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Remove the given job from a queue.
 */
void job_remove(queue *qp, job *jp)
{
    /* get wrlock, blocked by the existed rdlock but block the comming rdlock */
    pthread_rwlock_wrlock(&qp->q_lock);

    list_del(&(jp->node));
    qp->

    /* release wrlock */
    pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Find a job for the given thread ID.
 */
job *job_find(queue *qp, pthread_t id)
{
    job *jp;
    list_head *list;

    /* get rdlock, only blocked by wrlock */
    if (pthread_rwlock_rdlock(&qp->q_lock) != 0) {
        return (NULL);
    }

    list_for_each(list, &(qp->head)) {
        jp = list_entry(list, job, node);
        if (pthread_equal(jp->j_id, id)) {
            pthread_cond_signal(&cond);
            break;
        } else {
            jp = NULL;
        }
    }

    /* release rwlock */
    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}

/*=============================================================*/

static void reader()
{

}
