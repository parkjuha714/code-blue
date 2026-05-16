#ifndef PATIENT_H
#define PATIENT_H

// 상수 정의 
#define MAX_NAME_LEN    32      // 환자 이름 최대 길이
#define MAX_SYMPTOM_LEN 128     // 증상 설명 최대 길이
#define MAX_PATIENTS    100     // 최대 환자 수 (큐/우선순위 큐 크기)
#define MAX_LOG         10      // 최근 진료 기록 스택 크기

// 중증도 단계 (KTAS 기준)
// 숫자가 작을수록 위급함
#define SEVERITY_RESUSCITATION 1   // 최위급 (심정지, 호흡정지)
#define SEVERITY_EMERGENCY     2   // 긴급 (호흡곤란, 의식저하)
#define SEVERITY_URGENT        3   // 응급 (중등도 출혈, 심한 복통)
#define SEVERITY_LESS_URGENT   4   // 준응급 (경미한 골절)
#define SEVERITY_NON_URGENT    5   // 비응급 (가벼운 감기)

// 환자 구조체
typedef struct {
    int id;                         // 환자 고유 번호
    char name[MAX_NAME_LEN];        // 이름
    int age;                        // 나이
    char symptom[MAX_SYMPTOM_LEN];  // 증상
    int severity;                   // 중증도 (1~5)
    int arrival_time;               // 도착 순번 (접수 순서)
} Patient;

// 함수 선언
// 환자 정보를 사용자로부터 입력받아 Patient 구조체 반환
Patient input_patient(int id, int arrival_time);

// 환자 정보를 화면에 출력
void print_patient(const Patient* p);

// 중증도 숫자를 한글 명칭으로 변환
const char* severity_to_string(int severity);

#endif // PATIENT_H