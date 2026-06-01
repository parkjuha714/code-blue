#include <stdio.h>
#include <string.h>
#include "../include/triage.h"

// KTAS 1단계 (최위급/소생) 키워드
static const char *ktas_1_keywords[] = {
    "심정지", "심장정지", "의식없음", "무호흡",
    "호흡정지", "대량출혈", "쇼크", "혼수"};
static const int ktas_1_count = 8;

// KTAS 2단계 (긴급) 키워드
static const char *ktas_2_keywords[] = {
    "가슴통증", "흉통", "호흡곤란", "심한출혈",
    "마비", "발작", "경련", "의식저하", "심한복통"};
static const int ktas_2_count = 9;

// KTAS 3단계 (응급) 키워드
static const char *ktas_3_keywords[] = {
    "복통", "고열", "구토", "탈수",
    "심한두통", "호흡불편", "어지러움"};
static const int ktas_3_count = 7;

// KTAS 4단계 (준응급) 키워드
static const char *ktas_4_keywords[] = {
    "두통", "발열", "기침", "설사",
    "근육통", "관절통", "요통"};
static const int ktas_4_count = 7;

// KTAS 5단계 (비응급) 키워드
static const char *ktas_5_keywords[] = {
    "감기", "찰과상", "타박상", "가벼운상처",
    "콧물", "재채기", "피로"};
static const int ktas_5_count = 7;

// 자동 트리아지 함수 (선형 탐색)
int auto_triage(const char *symptom)
{
    if (symptom == NULL)
    {
        return 5;
    }

    // KTAS 1단계 검사 (가장 위급한 것부터)
    for (int i = 0; i < ktas_1_count; i++)
    {
        if (strstr(symptom, ktas_1_keywords[i]) != NULL)
        {
            return 1;
        }
    }

    // KTAS 2단계 검사
    for (int i = 0; i < ktas_2_count; i++)
    {
        if (strstr(symptom, ktas_2_keywords[i]) != NULL)
        {
            return 2;
        }
    }

    // KTAS 3단계 검사
    for (int i = 0; i < ktas_3_count; i++)
    {
        if (strstr(symptom, ktas_3_keywords[i]) != NULL)
        {
            return 3;
        }
    }

    // KTAS 4단계 검사
    for (int i = 0; i < ktas_4_count; i++)
    {
        if (strstr(symptom, ktas_4_keywords[i]) != NULL)
        {
            return 4;
        }
    }

    // KTAS 5단계 검사
    for (int i = 0; i < ktas_5_count; i++)
    {
        if (strstr(symptom, ktas_5_keywords[i]) != NULL)
        {
            return 5;
        }
    }

    // 매칭 안 되면 기본값
    return 5;
}

// KTAS 단계명 반환
const char *get_ktas_name(int level)
{
    switch (level)
    {
    case 1:
        return "최위급";
    case 2:
        return "긴급";
    case 3:
        return "응급";
    case 4:
        return "준응급";
    case 5:
        return "비응급";
    default:
        return "알수없음";
    }
}