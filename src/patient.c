#include <stdio.h>
#include <string.h>
#include "../include/patient.h"
#include "../include/triage.h"

// 환자 정보를 사용자로부터 입력받아 Patient 구조체로 반환
// 증상은 자동 트리아지로 KTAS 단계 자동 분류
Patient input_patient(int id, int arrival_time)
{
    Patient p;
    p.id = id;
    p.arrival_time = arrival_time;

    // 이름 입력
    printf("환자 이름을 입력하세요: ");
    scanf(" %31[^\n]", p.name);

    // 나이 입력
    printf("나이를 입력하세요: ");
    while (scanf("%d", &p.age) != 1 || p.age < 0 || p.age > 150)
    {
        printf("⚠️ 올바른 나이를 입력하세요 (0~150): ");
        while (getchar() != '\n')
            ;
    }

    // 증상 입력
    printf("증상을 입력하세요: ");
    scanf(" %127[^\n]", p.symptom);

    // 자동 트리아지: 증상 → KTAS 단계 자동 분류
    p.severity = auto_triage(p.symptom);

    return p;
}

// 환자 정보를 화면에 출력
void print_patient(const Patient *p)
{
    printf("  [접수번호 %d] %s (%d세) - %s\n",
           p->id, p->name, p->age, p->symptom);
    printf("    → KTAS %d단계 (%s)\n",
           p->severity, severity_to_string(p->severity));
}

// 중증도 숫자를 한글 명칭으로 변환
const char *severity_to_string(int severity)
{
    switch (severity)
    {
    case SEVERITY_RESUSCITATION:
        return "최위급";
    case SEVERITY_EMERGENCY:
        return "긴급";
    case SEVERITY_URGENT:
        return "응급";
    case SEVERITY_LESS_URGENT:
        return "준응급";
    case SEVERITY_NON_URGENT:
        return "비응급";
    default:
        return "알수없음";
    }
}