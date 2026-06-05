#include <stdio.h>
#include <stdlib.h>
#include "../include/patient.h"
#include "../include/queue.h"
#include "../include/pqueue.h"
#include "../include/stack.h"
#include "../include/triage.h"
#include "../include/ui.h"
#include "../include/fileio.h"

/* ─────────────────────────────────────────────
   Code Blue - 응급실 환자 접수 및 진료 관리 시스템

   [자료구조 흐름]
   1. 환자 접수    → 일반 대기 큐(queue, FIFO)
   2. 다음 환자 호출 → 큐에서 꺼내 우선순위 큐(pqueue, 중증도순)로 이동
   3. 진료 완료    → 우선순위 큐에서 가장 급한 환자를 꺼내 스택(기록)에 저장
   4. 되돌리기     → 스택 pop
   ───────────────────────────────────────────── */

// 전역 자료구조 (메뉴 간 데이터 유지)
Queue waiting_queue;        // 일반 대기 큐 (선착순)
PriorityQueue triage_queue; // 우선순위 큐 (중증도순)
Stack treatment_log;        // 진료 완료 기록 스택

// 환자 접수 번호 (증가하면서 ID로 사용)
int next_patient_id = 1;

// 도착 순번 (접수 순서)
int next_arrival_time = 1;

/* ── [1] 환자 접수: 정보 입력 후 일반 대기 큐에 추가 ── */
void register_patient(void)
{
    ui_divider();
    printf("  ▶ 환자 접수\n\n");

    if (queue_is_full(&waiting_queue))
    {
        printf("  ⚠ 대기실이 가득 찼습니다. 더 이상 접수할 수 없습니다.\n");
        return;
    }

    // 환자 정보 입력 + 자동 트리아지
    Patient p = input_patient(next_patient_id, next_arrival_time);

    if (queue_enqueue(&waiting_queue, p))
    {
        printf("\n  ✔ 환자 접수 완료!\n");
        print_patient(&p);
        next_patient_id++;
        next_arrival_time++;
    }
    else
    {
        printf("  ⚠ 접수에 실패했습니다.\n");
    }
}

/* ── [2] 다음 환자 호출: 대기 큐 → 우선순위 큐로 이동 ── */
void call_next_patient(void)
{
    ui_divider();
    printf("  ▶ 다음 환자 호출\n\n");

    if (queue_is_empty(&waiting_queue))
    {
        printf("  ⚠ 대기 중인 환자가 없습니다.\n");
        return;
    }

    Patient p;
    queue_dequeue(&waiting_queue, &p);

    printf("  호출된 환자:\n");
    print_patient(&p);

    // 우선순위 큐로 이동 (중증도순 정렬)
    if (pqueue_enqueue(&triage_queue, p))
    {
        printf("\n  ✔ 우선순위 진료 대기열에 등록되었습니다.\n");
    }
    else
    {
        printf("  ⚠ 우선순위 대기열이 가득 찼습니다.\n");
    }
}

/* ── [3] 진료 완료: 우선순위 큐에서 가장 급한 환자 → 진료 기록 스택 ── */
void complete_treatment(void)
{
    ui_divider();
    printf("  ▶ 진료 완료 처리\n\n");

    if (pqueue_is_empty(&triage_queue))
    {
        printf("  ⚠ 진료할 환자가 없습니다. (먼저 환자를 호출하세요)\n");
        return;
    }

    Patient p;
    pqueue_dequeue(&triage_queue, &p);

    printf("  진료 완료 환자:\n");
    print_patient(&p);

    // 진료 기록 스택에 push
    stack_push(&treatment_log, p);
    printf("\n  ✔ 진료 기록이 저장되었습니다.\n");
    printf("  현재 진료 기록: %d / %d\n", stack_size(&treatment_log), STACK_MAX);
}

/* ── 메인 ── */
int main(void)
{
    int choice;
    int running = 1;

    // 자료구조 초기화
    queue_init(&waiting_queue);
    pqueue_init(&triage_queue);
    stack_init(&treatment_log);

    // 프로그램 시작 시 저장된 진료 기록 불러오기
    ui_load(&treatment_log);

    printf("\n  시스템을 시작합니다...\n");

    while (running)
    {
        ui_print_main_menu();

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("\n  ⚠ 숫자를 입력해주세요.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            register_patient();
            break;
        case 2:
            call_next_patient();
            break;
        case 3:
            complete_treatment();
            break;
        case 4:
            ui_undo_treatment(&treatment_log);
            break;
        case 5:
            ui_peek_treatment(&treatment_log);
            break;
        case 6:
            ui_show_treatment_log(&treatment_log);
            break;
        case 7:
            ui_divider();
            printf("  ▶ 대기 현황 조회\n\n");
            printf("  대기 인원: %d명\n\n", queue_size(&waiting_queue));
            queue_print_all(&waiting_queue);
            break;
        case 8:
            ui_save(&treatment_log);
            break;
        case 9:
            ui_load(&treatment_log);
            break;
        case 0:
            printf("\n  시스템을 종료합니다. 수고하셨습니다.\n");
            running = 0;
            break;
        default:
            printf("\n  ⚠ 잘못된 선택입니다. 0~9 사이의 숫자를 입력하세요.\n");
            break;
        }
    }

    return 0;
}