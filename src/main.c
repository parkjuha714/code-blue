#include <stdio.h>
#include <stdlib.h>
#include "../include/patient.h"

// 메뉴 선택지를 화면에 출력
void print_menu(void) {
    printf("\n");
    printf("========================================\n");
    printf("    Code Blue - ER Triage System\n");
    printf("========================================\n");
    printf(" 1. 환자 접수\n");
    printf(" 2. 다음 환자 호출\n");
    printf(" 3. 대기 현황 조회\n");
    printf(" 4. 최근 진료 되돌리기\n");
    printf(" 5. 진료 통계 보기\n");
    printf(" 0. 종료\n");
    printf("========================================\n");
    printf(" 메뉴 선택 >> ");
}

int main(void) {
    int choice;
    int running = 1;

    printf("시스템을 시작합니다...\n");

    while (running) {
        print_menu();

        if (scanf("%d", &choice) != 1) {
            // 숫자가 아닌 입력이 들어온 경우 버퍼 비우기
            while (getchar() != '\n');
            printf("⚠️  숫자를 입력해주세요.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("\n[환자 접수] 기능은 아직 구현 중입니다.\n");
                break;
            case 2:
                printf("\n[다음 환자 호출] 기능은 아직 구현 중입니다.\n");
                break;
            case 3:
                printf("\n[대기 현황 조회] 기능은 아직 구현 중입니다.\n");
                break;
            case 4:
                printf("\n[최근 진료 되돌리기] 기능은 아직 구현 중입니다.\n");
                break;
            case 5:
                printf("\n[진료 통계 보기] 기능은 아직 구현 중입니다.\n");
                break;
            case 0:
                printf("\n시스템을 종료합니다. 수고하셨습니다.\n");
                running = 0;
                break;
            default:
                printf("\n⚠️  잘못된 선택입니다. 0~5 사이의 숫자를 입력하세요.\n");
                break;
        }
    }

    return 0;
}