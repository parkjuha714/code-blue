#include <stdio.h>
#include "../include/queue.h"
#include "../include/patient.h"

/*
 * 원형 큐 (Circular Queue) 구현
 * 일반 대기 환자를 선착순(FIFO)으로 관리
 */

// 큐 초기화: 모든 인덱스를 0으로 리셋
void queue_init(Queue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// 큐가 비어있는지 확인
int queue_is_empty(const Queue *q)
{
    return q->count == 0;
}

// 큐가 가득 찼는지 확인
int queue_is_full(const Queue *q)
{
    return q->count == MAX_PATIENTS;
}

// 큐에 환자 추가 (rear 위치에 삽입)
int queue_enqueue(Queue *q, Patient p)
{
    if (queue_is_full(q))
    {
        printf("⚠️  대기실이 가득 찼습니다. (최대 %d명)\n", MAX_PATIENTS);
        return 0; // 실패
    }

    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % MAX_PATIENTS; // 원형: 끝에 도달하면 0으로
    q->count++;

    return 1; // 성공
}

// 큐에서 환자 꺼내기 (front 위치에서 제거)
int queue_dequeue(Queue *q, Patient *out)
{
    if (queue_is_empty(q))
    {
        printf("⚠️  대기 중인 일반 환자가 없습니다.\n");
        return 0; // 실패
    }

    *out = q->data[q->front];                 // 환자 정보 복사
    q->front = (q->front + 1) % MAX_PATIENTS; // 원형: 끝에 도달하면 0으로
    q->count--;

    return 1; // 성공
}

// 큐에 있는 모든 환자 출력
void queue_print_all(const Queue *q)
{
    if (queue_is_empty(q))
    {
        printf("(일반 대기 환자 없음)\n");
        return;
    }

    printf("\n일반 대기 환자 목록 (%d명)\n", q->count);
    int idx = q->front;
    for (int i = 0; i < q->count; i++)
    {
        const Patient *p = &q->data[idx];
        printf("[%d번째] ID:%d  이름:%s  나이:%d  증상:%s  중증도:%d\n",
               i + 1, p->id, p->name, p->age, p->symptom, p->severity);
        idx = (idx + 1) % MAX_PATIENTS; // 다음 환자 (원형 순회)
    }
    printf("\n");
}

// 현재 큐 크기 반환
int queue_size(const Queue *q)
{
    return q->count;
}