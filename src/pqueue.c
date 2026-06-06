#include <stdio.h>
#include "../include/pqueue.h"
#include "../include/patient.h"

/*
 * 우선순위 큐 (배열 기반, 삽입 정렬 방식)
 * severity(중증도) 숫자가 작을수록 우선순위가 높음 (KTAS 1단계 = 최위급)
 * 같은 중증도면 먼저 도착한(arrival_time이 작은) 환자가 우선
 */

// 우선순위 큐 초기화
void pqueue_init(PriorityQueue *pq)
{
    pq->count = 0;
}

// 큐가 비어있는지 확인
int pqueue_is_empty(const PriorityQueue *pq)
{
    return pq->count == 0;
}

// 큐가 가득 찼는지 확인
int pqueue_is_full(const PriorityQueue *pq)
{
    return pq->count == MAX_PATIENTS;
}

// 환자 추가: 중증도 순서에 맞는 위치를 찾아 끼워넣는다 (삽입 정렬)
int pqueue_enqueue(PriorityQueue *pq, Patient p)
{
    if (pqueue_is_full(pq))
    {
        printf("⚠️ 우선순위 큐가 가득 찼습니다.\n");
        return 0;
    }

    // 맨 뒤에서부터 비교하며, 새 환자보다 우선순위 낮은 환자들을 한 칸씩 뒤로 민다
    int i = pq->count - 1;

    while (i >= 0)
    {
        int move = 0;

        // 기존 환자가 더 안 급하면(중증도 숫자 큼) 뒤로 밀어야 함
        if (pq->data[i].severity > p.severity)
        {
            move = 1;
        }
        // 중증도가 같으면, 늦게 온 환자를 뒤로 밀어 먼저 온 환자를 앞세움
        else if (pq->data[i].severity == p.severity &&
                 pq->data[i].arrival_time > p.arrival_time)
        {
            move = 1;
        }

        if (!move)
            break; // 제자리를 찾았으면 멈춤

        pq->data[i + 1] = pq->data[i]; // 한 칸 뒤로 이동
        i--;
    }

    pq->data[i + 1] = p; // 찾은 위치에 새 환자 삽입
    pq->count++;

    return 1;
}

// 가장 급한 환자 꺼내기 (맨 앞 = 우선순위 1등)
int pqueue_dequeue(PriorityQueue *pq, Patient *out)
{
    if (pqueue_is_empty(pq))
    {
        printf("⚠️ 대기 중인 응급 환자가 없습니다.\n");
        return 0;
    }

    *out = pq->data[0]; // 맨 앞 환자가 가장 급함

    // 나머지를 한 칸씩 앞으로 당겨 빈자리를 메움
    for (int i = 1; i < pq->count; i++)
    {
        pq->data[i - 1] = pq->data[i];
    }

    pq->count--;

    return 1;
}

// 우선순위 큐의 모든 환자 출력 (앞쪽일수록 우선순위 높음)
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

// 현재 큐 크기 반환
int pqueue_size(const PriorityQueue *pq)
{
    return pq->count;
}