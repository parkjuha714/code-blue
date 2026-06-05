#ifndef UI_H
#define UI_H

#include "stack.h"

// ── 나영 담당 UI 함수 ──────────────────────────

// 진료 완료 처리: 환자 정보 입력 후 스택에 push
void ui_push_treatment(Stack *s, int *next_id);

// 되돌리기: 스택에서 pop, 최근 진료 기록 취소
void ui_undo_treatment(Stack *s);

// 최근 진료 기록 peek (꺼내지 않고 확인)
void ui_peek_treatment(const Stack *s);

// 진료 완료 기록 전체 보기
void ui_show_treatment_log(const Stack *s);

// 파일 저장 메뉴
void ui_save(const Stack *s);

// 파일 불러오기 메뉴
void ui_load(Stack *s);

// 구분선 출력 유틸
void ui_divider(void);

// 메인 메뉴 출력
void ui_print_main_menu(void);

#endif
