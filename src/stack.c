#include <stdio.h>
#include "../include/stack.h"

/* ────────────────────────────────────────────
   스택 (배열 기반 LIFO)
   최대 STACK_MAX(10)개 진료 완료 기록 유지
   ──────────────────────────────────────────── */

void stack_init(Stack *s)
{
    s->top = -1;
}

int stack_is_full(const Stack *s)
{
    return s->top == STACK_MAX - 1;
}

int stack_is_empty(const Stack *s)
{
    return s->top == -1;
}

/* push: 진료 완료 환자를 스택에 쌓는다.
   최대 10개를 유지하기 위해 가득 찬 경우
   가장 오래된 기록(인덱스 0)을 제거하고 한 칸씩 앞으로 민다. */
int stack_push(Stack *s, Patient p)
{
    if (stack_is_full(s))
    {
        // 가장 오래된 기록 제거 후 시프트
        int i;
        for (i = 0; i < STACK_MAX - 1; i++)
        {
            s->data[i] = s->data[i + 1];
        }
        s->data[STACK_MAX - 1] = p;
        // top은 STACK_MAX-1 그대로 유지
        return 1;
    }
    s->top++;
    s->data[s->top] = p;
    return 1;
}

/* pop: 가장 최근 진료 기록을 꺼낸다. (되돌리기) */
int stack_pop(Stack *s, Patient *out)
{
    if (stack_is_empty(s))
    {
        return 0;
    }
    *out = s->data[s->top];
    s->top--;
    return 1;
}

/* peek: 꺼내지 않고 최근 기록만 확인한다. */
int stack_peek(const Stack *s, Patient *out)
{
    if (stack_is_empty(s))
    {
        return 0;
    }
    *out = s->data[s->top];
    return 1;
}

/* 스택 전체 출력 (최신순: top → 0) */
void stack_print(const Stack *s)
{
    if (stack_is_empty(s))
    {
        printf("  (진료 기록이 없습니다)\n");
        return;
    }
    int rank = 1;
    for (int i = s->top; i >= 0; i--)
    {
        printf("  %d. [접수번호 %d] %s (%d세) - %s\n",
               rank++,
               s->data[i].id,
               s->data[i].name,
               s->data[i].age,
               s->data[i].symptom);
        printf("     → KTAS %d단계\n", s->data[i].severity);
    }
}
int stack_size(const Stack *s)
{
    return s->top + 1;
}
