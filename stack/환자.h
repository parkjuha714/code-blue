#ifndef PATIENT_H
#define PATIENT_H

// 환자 구조체 (제안서 정의 그대로)
typedef struct {
    int id;
    char name[32];
    int age;
    char symptom[128];
    int severity;       // 1(최위급) ~ 5(경증)
    int arrival_time;
} Patient;

// 환자 정보 출력
void print_patient(const Patient *p);

// 환자 정보 입력
void input_patient(Patient *p);

#endif
