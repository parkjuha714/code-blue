#ifndef STACK_H
#define STACK_H

#include "patient.h"

#define STACK_MAX 10 // 제안서: 최대 10개 기록 유지

// 스택 구조체
typedef struct
{
    Patient data[STACK_MAX];
    int top; // -1이면 빈 스택
} Stack;

// 스택 초기화
void stack_init(Stack *s);

// 스택이 가득 찼는지
int stack_is_full(const Stack *s);

// 스택이 비었는지
int stack_is_empty(const Stack *s);

// push: 진료 완료 환자 기록 저장
// 반환: 1 성공, 0 실패(가득 참)
int stack_push(Stack *s, Patient p);

// pop: 최근 진료 기록 꺼내기 (되돌리기)
// 반환: 1 성공, 0 실패(비어 있음)
int stack_pop(Stack *s, Patient *out);

// peek: 꺼내지 않고 최근 기록 확인
// 반환: 1 성공, 0 실패(비어 있음)
int stack_peek(const Stack *s, Patient *out);

// 스택 전체 내용 출력
void stack_print(const Stack *s);

// 스택 크기(현재 저장된 개수) 반환
int stack_size(const Stack *s);

#endif
