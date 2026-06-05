#ifndef FILE_IO_H
#define FILE_IO_H

#include "스택.h"

#define DATA_FILE "data/patients.csv"

// 진료 완료 기록(스택)을 CSV로 저장
// 반환: 저장된 레코드 수, -1이면 실패
int save_data(const Stack *s);

// CSV에서 진료 기록을 스택으로 불러오기
// 반환: 불러온 레코드 수, -1이면 실패
int load_data(Stack *s);

#endif
