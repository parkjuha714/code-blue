#ifndef PQUEUE_H
#define PQUEUE_H

#include "patient.h"

typedef struct
{
    Patient data[MAX_PATIENTS];
    int count;
} PriorityQueue;

void pqueue_init(PriorityQueue *pq);

int pqueue_is_empty(const PriorityQueue *pq);

int pqueue_is_full(const PriorityQueue *pq);

int pqueue_enqueue(PriorityQueue *pq, Patient p);

int pqueue_dequeue(PriorityQueue *pq, Patient *out);

void pqueue_print_all(const PriorityQueue *pq);

int pqueue_size(const PriorityQueue *pq);

#endif