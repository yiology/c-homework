//结构体指针与遍历

#include <stdio.h>

struct Student {
    char name[20];
    int score;
};

int main() {
    struct Student stus[3];
    struct Student *p = stus;
    struct Student *max_stu = stus;

    // 输入
    for (int i = 0; i < 3; i++) {
        printf("输入第 %d 个学生姓名和成绩: ", i + 1);
        scanf("%s %d", (p + i)->name, &(p + i)->score);
    }

    // 遍历并找最高分
    printf("\n学生列表：\n");
    for (int i = 0; i < 3; i++) {
        printf("姓名: %s \t 成绩: %d\n", (p + i)->name, (p + i)->score);
        if ((p + i)->score > max_stu->score) {
            max_stu = (p + i);
        }
    }

    printf("\n最高分学生: %s (%d分)\n", max_stu->name, max_stu->score);

    return 0;
}
