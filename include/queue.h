#ifndef QUEUE_H
#define QUEUE_H

#include "patient.h"

/*
 * 원형 큐 (Circular Queue)
 * 일반 대기 환자를 선착순(FIFO)으로 관리한다.
 *
 * 배열 기반으로 구현하며, front/rear 인덱스를 순환시켜 메모리를 효율적으로 사용.
 * 환자가 들어오면 rear에 추가(enqueue), 호출되면 front에서 제거(dequeue).
 */

// 큐 구조체
typedef struct
{
    Patient data[MAX_PATIENTS]; // 환자 데이터 저장 배열
    int front;                  // 가장 먼저 들어온 환자의 위치
    int rear;                   // 가장 최근에 들어온 환자의 다음 위치
    int count;                  // 현재 큐에 있는 환자 수
} Queue;

// ===== 함수 선언 =====

// 큐 초기화 (front=0, rear=0, count=0)
void queue_init(Queue *q);

// 큐가 비어있는지 확인 (1: 비어있음, 0: 아님)
int queue_is_empty(const Queue *q);

// 큐가 가득 찼는지 확인 (1: 가득 참, 0: 아님)
int queue_is_full(const Queue *q);

// 큐에 환자 추가 (성공: 1, 실패: 0)
int queue_enqueue(Queue *q, Patient p);

// 큐에서 환자 꺼내기 (성공: 1, 실패: 0)
// 꺼낸 환자 정보는 out 포인터에 저장
int queue_dequeue(Queue *q, Patient *out);

// 큐에 있는 모든 환자 출력
void queue_print_all(const Queue *q);

// 현재 큐 크기 반환
int queue_size(const Queue *q);

#endif // QUEUE_H