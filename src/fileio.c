#include <stdio.h>
#include <string.h>
#include "../include/fileio.h"

/* ─────────────────────────────────────────────
   CSV 형식:  id,name,age,symptom,severity,arrival_time
   ───────────────────────────────────────────── */

int save_data(const Stack *s)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp)
    {
        perror("  [오류] 파일 열기 실패");
        return -1;
    }

    // 헤더
    fprintf(fp, "id,name,age,symptom,severity,arrival_time\n");

    int count = 0;
    int i;
    for (i = 0; i <= s->top; i++)
    {
        const Patient *p = &s->data[i];
        // symptom에 쉼표가 있을 수 있으므로 큰따옴표로 감쌈
        fprintf(fp, "%d,%s,%d,\"%s\",%d,%d\n",
                p->id, p->name, p->age,
                p->symptom, p->severity, p->arrival_time);
        count++;
    }

    fclose(fp);
    return count;
}

int load_data(Stack *s)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp)
    {
        // 파일 없음 = 첫 실행, 오류 아님
        return 0;
    }

    char line[256];
    // 헤더 스킵
    if (!fgets(line, sizeof(line), fp))
    {
        fclose(fp);
        return 0;
    }

    stack_init(s);
    int count = 0;

    while (fgets(line, sizeof(line), fp))
    {
        Patient p;
        char symptom_buf[128];

        // CSV 파싱: symptom은 "..." 큰따옴표 안에 있을 수 있음
        int matched = sscanf(line,
                             "%d,%31[^,],%d,\"%127[^\"]\",%d,%d",
                             &p.id, p.name, &p.age,
                             symptom_buf, &p.severity, &p.arrival_time);

        if (matched < 6)
        {
            // 큰따옴표 없는 경우 재시도
            matched = sscanf(line,
                             "%d,%31[^,],%d,%127[^,],%d,%d",
                             &p.id, p.name, &p.age,
                             symptom_buf, &p.severity, &p.arrival_time);
        }

        if (matched == 6)
        {
            strncpy(p.symptom, symptom_buf, 127);
            p.symptom[127] = '\0';
            stack_push(s, p);
            count++;
        }
    }

    fclose(fp);
    return count;
}
