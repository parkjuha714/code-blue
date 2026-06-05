#include <stdio.h>
#include <time.h>
#include "../include/ui.h"
#include "../include/fileio.h"

/* ─────────────────────────────────────────────
   ui.c  –  UI / 메뉴 출력
   - 진료 완료 처리 (push)
   - 되돌리기 (undo / pop)
   - peek / 기록 조회
   - 파일 저장/불러오기
   ───────────────────────────────────────────── */

void ui_divider(void)
{
    printf("\n  ══════════════════════════════════════════\n");
}

void ui_print_main_menu(void)
{
    ui_divider();
    printf("  ██  응급실 환자 접수 및 진료 관리 시스템  ██\n");
    ui_divider();
    printf("  [1] 환자 접수\n");
    printf("  [2] 다음 환자 호출\n");
    printf("  [3] 진료 완료 처리\n");
    printf("  [4] 되돌리기\n");
    printf("  [5] 최근 진료 확인\n");
    printf("  [6] 진료 완료 기록 조회\n");
    printf("  [7] 대기 현황 조회\n");
    printf("  [8] 파일 저장\n");
    printf("  [9] 파일 불러오기\n");
    printf("  [0] 종료\n");
    ui_divider();
    printf("  선택 >> ");
}

/* ── 진료 완료 처리: 환자 정보 입력 후 push ── */
void ui_push_treatment(Stack *s, int *next_id)
{
    ui_divider();
    printf("  ▶ 진료 완료 처리\n\n");

    if (stack_is_full(s))
    {
        printf("  ⚠ 스택이 가득 찼습니다 (최대 %d개).\n", STACK_MAX);
        printf("    가장 오래된 기록을 자동으로 제거하고 저장합니다.\n\n");
    }

    printf("  진료 완료 환자 정보를 입력하세요.\n");
    Patient p = input_patient(*next_id, (int)time(NULL));

    stack_push(s, p);
    (*next_id)++;

    printf("\n  ✔ 진료 기록이 저장되었습니다. (ID: %d, 이름: %s)\n",
           p.id, p.name);
    printf("  현재 스택 크기: %d / %d\n", stack_size(s), STACK_MAX);
}

/* ── 되돌리기: pop ── */
void ui_undo_treatment(Stack *s)
{
    ui_divider();
    printf("  ▶ 되돌리기 - 최근 진료 기록 취소\n\n");

    if (stack_is_empty(s))
    {
        printf("  ⚠ 되돌릴 기록이 없습니다. 스택이 비어 있습니다.\n");
        return;
    }

    // pop 전에 확인 메시지
    Patient preview;
    stack_peek(s, &preview);
    printf("  취소할 기록:\n");
    print_patient(&preview);
    printf("\n  정말 취소하시겠습니까? (y/n): ");

    char ch;
    scanf(" %c", &ch);
    if (ch != 'y' && ch != 'Y')
    {
        printf("  취소 작업을 중단했습니다.\n");
        return;
    }

    Patient removed;
    stack_pop(s, &removed);
    printf("\n  ✔ 진료 기록이 취소되었습니다: %s (ID: %d)\n",
           removed.name, removed.id);
    printf("  남은 기록 수: %d개\n", stack_size(s));
}

/* ── peek: 꺼내지 않고 확인 ── */
void ui_peek_treatment(const Stack *s)
{
    ui_divider();
    printf("  ▶ 최근 진료 기록 확인\n\n");

    Patient p;
    if (!stack_peek(s, &p))
    {
        printf("  ⚠ 기록이 없습니다. 스택이 비어 있습니다.\n");
        return;
    }

    printf("  가장 최근 진료 완료 환자:\n");
    print_patient(&p);
}

/* ── 기록 전체 조회 ── */
void ui_show_treatment_log(const Stack *s)
{
    ui_divider();
    printf("  ▶ 진료 완료 기록 전체 조회 (최신순)\n\n");
    printf("  총 %d개 기록 (최대 %d개 유지)\n\n", stack_size(s), STACK_MAX);
    stack_print(s);
}

/* ── 파일 저장 ── */
void ui_save(const Stack *s)
{
    ui_divider();
    printf("  ▶ 데이터 저장\n\n");

    int n = save_data(s);
    if (n < 0)
    {
        printf("  ✘ 저장에 실패했습니다.\n");
    }
    else
    {
        printf("  ✔ %d개 기록을 저장했습니다.\n", n);
    }
}

/* ── 파일 불러오기 ── */
void ui_load(Stack *s)
{
    ui_divider();
    printf("  ▶ 데이터 불러오기\n\n");

    int n = load_data(s);
    if (n < 0)
    {
        printf("  ✘ 불러오기에 실패했습니다.\n");
    }
    else if (n == 0)
    {
        printf("  저장된 데이터가 없습니다.\n");
    }
    else
    {
        printf("  ✔ %d개 기록을 불러왔습니다.\n", n);
    }
}