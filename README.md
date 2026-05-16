# Code Blue

응급실 환자 접수 및 진료 관리 시스템 — 자료구조 팀 프로젝트

## 프로젝트 개요

응급실에 도착하는 환자를 큐, 우선순위 큐, 스택을 활용하여 효율적으로 관리하는 C 기반 콘솔 프로그램입니다.

- 일반 환자는 선착순(FIFO)으로 대기
- 위급 환자는 중증도에 따라 우선 진료
- 최근 진료 기록은 스택으로 관리하여 되돌리기 지원

## 사용 자료구조

| 자료구조 | 역할 |
| --- | --- |
| 원형 큐 (Circular Queue) | 일반 대기 환자 관리 |
| 우선순위 큐 (Priority Queue) | 위급도 기반 우선 진료 |
| 스택 (Stack) | 최근 진료 기록 및 되돌리기 |

## 폴더 구조

```
code-blue/
├── src/         소스 코드 (.c)
├── include/     헤더 파일 (.h)
├── data/        환자 데이터 (CSV)
├── docs/        문서 및 발표 자료
├── README.md
└── .gitignore
```

## 컴파일 및 실행

```bash
clang -I include src/*.c -o code-blue
./code-blue
```

## 개발 환경

- macOS (Apple Silicon)
- clang (Apple LLVM)
- VS Code

## 팀원

- parkjuha714
- (팀원 B)

## 개발 기간

2026.05 ~ 2026.06 (4주)
