#include <stdio.h>
#include "../include/pqueue.h"
#include "../include/patient.h"

/*
 * 우선순위 큐 구현
 * severity 숫자가 작을수록 우선순위가 높음
 */

void pqueue_init(PriorityQueue *pq)
{
    pq->count = 0;
}

int pqueue_is_empty(const PriorityQueue *pq)
{
    return pq->count == 0;
}

int pqueue_is_full(const PriorityQueue *pq)
{
    return pq->count == MAX_PATIENTS;
}

int pqueue_enqueue(PriorityQueue *pq, Patient p)
{
    if (pqueue_is_full(pq))
    {
        printf("⚠️ 우선순위 큐가 가득 찼습니다.\n");
        return 0;
    }

    int i = pq->count - 1;

    while (i >= 0)
    {
        int move = 0;

        if (pq->data[i].severity > p.severity)
        {
            move = 1;
        }
        else if (pq->data[i].severity == p.severity &&
                 pq->data[i].arrival_time > p.arrival_time)
        {
            move = 1;
        }

        if (!move)
            break;

        pq->data[i + 1] = pq->data[i];
        i--;
    }

    pq->data[i + 1] = p;
    pq->count++;

    return 1;
}

int pqueue_dequeue(PriorityQueue *pq, Patient *out)
{
    if (pqueue_is_empty(pq))
    {
        printf("⚠️ 대기 중인 응급 환자가 없습니다.\n");
        return 0;
    }

    *out = pq->data[0];

    for (int i = 1; i < pq->count; i++)
    {
        pq->data[i - 1] = pq->data[i];
    }

    pq->count--;

    return 1;
}

void pqueue_print_all(const PriorityQueue *pq)
{
    if (pqueue_is_empty(pq))
    {
        printf("(응급 환자 없음)\n");
        return;
    }

    printf("\n응급 환자 목록 (%d명)\n", pq->count);

    for (int i = 0; i < pq->count; i++)
    {
        const Patient *p = &pq->data[i];

        printf("[%d번째] ID:%d 이름:%s 나이:%d 증상:%s 중증도:%d\n",
               i + 1,
               p->id,
               p->name,
               p->age,
               p->symptom,
               p->severity);
    }

    printf("\n");
}

int pqueue_size(const PriorityQueue *pq)
{
    return pq->count;
}