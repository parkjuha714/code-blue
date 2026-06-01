#include <stdio.h>
#include <stdlib.h>
#include "../include/patient.h"
#include "../include/queue.h"
#include "../include/triage.h"

// 전역 변수: 일반 대기 환자 큐
Queue waiting_queue;

// 환자 접수 번호 (증가하면서 ID로 사용)
int next_patient_id = 1;

// 도착 순번 (접수 순서)
int next_arrival_time = 1;

// 메뉴 선택지를 화면에 출력
void print_menu(void)
{
    printf("\n");
    printf("\n");
    printf("  Code Blue - ER Triage System\n");
    printf("\n");
    printf(" 1. 환자 접수\n");
    printf(" 2. 다음 환자 호출\n");
    printf(" 3. 대기 현황 조회\n");
    printf(" 4. 최근 진료 되돌리기\n");
    printf(" 5. 진료 통계 보기\n");
    printf(" 0. 종료\n");
    printf("\n");
    printf(" 메뉴 선택 >> ");
}

// 환자 접수 기능
// 1. 사용자로부터 환자 정보 입력받기
// 2. 자동 트리아지로 KTAS 단계 결정
// 3. 대기 큐에 추가
void register_patient(void)
{
    printf("\n환자 접수\n");

    // 큐가 가득 찼는지 확인
    if (queue_is_full(&waiting_queue))
    {
        printf("⚠️ 대기실이 가득 찼습니다. 더 이상 접수할 수 없습니다.\n");
        return;
    }

    // 환자 정보 입력 + 자동 트리아지
    Patient p = input_patient(next_patient_id, next_arrival_time);

    // 큐에 추가
    if (queue_enqueue(&waiting_queue, p))
    {
        printf("\n✅ 환자 접수 완료!\n");
        print_patient(&p);

        // 다음 환자 번호 증가
        next_patient_id++;
        next_arrival_time++;
    }
    else
    {
        printf("⚠️ 접수에 실패했습니다.\n");
    }
}

int main(void)
{
    int choice;
    int running = 1;

    // 큐 초기화
    queue_init(&waiting_queue);

    printf("시스템을 시작합니다...\n");

    while (running)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            // 숫자가 아닌 입력이 들어온 경우 버퍼 비우기
            while (getchar() != '\n')
                ;
            printf("⚠️ 숫자를 입력해주세요.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            register_patient();
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
            printf("\n⚠️ 잘못된 선택입니다. 0~5 사이의 숫자를 입력하세요.\n");
            break;
        }
    }

    return 0;
}