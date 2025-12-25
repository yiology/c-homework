//编程实现学生成绩管理系统。
//它包含了实际开发中所需的全部核心功能：增、删、改、查、排序，以及最重要的文件读写（数据持久化），确保程序关闭后数据不会丢失。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === 定义常量与结构体 ===
#define MAX_STUDENTS 100
#define FILE_NAME "students.txt"

typedef struct {
    char id[20];        // 学号
    char name[30];      // 姓名
    float c_lang;       // C语言成绩
    float math;         // 数学成绩
    float english;      // 英语成绩
    float total;        // 总分
    float average;      // 平均分
} Student;

// === 全局变量 ===
Student students[MAX_STUDENTS];
int count = 0; // 当前学生数量

// === 函数声明 ===
void load_from_file();
void save_to_file();
void input_student();
void delete_student();
void modify_student();
void search_student();
void print_all();
void sort_by_total();
void calculate_score(Student *s);
int find_index_by_id(const char *id);
void clear_screen();
void pause_screen();

// === 主函数 ===
int main() {
    // 程序启动时加载数据
    load_from_file();

    int choice;
    while (1) {
        clear_screen();
        printf("===================================\n");
        printf("      学生成绩管理系统 v1.0\n");
        printf("===================================\n");
        printf("  1. 录入学生信息\n");
        printf("  2. 删除学生信息\n");
        printf("  3. 修改学生信息\n");
        printf("  4. 查询学生信息\n");
        printf("  5. 显示所有学生\n");
        printf("  6. 按总分排序\n");
        printf("  0. 保存并退出\n");
        printf("===================================\n");
        printf("请输入选项: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        switch (choice) {
            case 1: input_student(); break;
            case 2: delete_student(); break;
            case 3: modify_student(); break;
            case 4: search_student(); break;
            case 5: print_all(); break;
            case 6: sort_by_total(); break;
            case 0:
                save_to_file();
                printf("数据已保存，程序退出。\n");
                return 0;
            default:
                printf("无效选项！\n");
                pause_screen();
        }
    }
    return 0;
}

// === 辅助函数 ===

void clear_screen() {
    // 兼容 Linux/Mac (Windows下请改为 system("cls"))
    printf("\033[H\033[J"); 
}

void pause_screen() {
    printf("\n按回车键继续...");
    getchar(); getchar(); // 吞掉之前的换行符并等待输入
}

void calculate_score(Student *s) {
    s->total = s->c_lang + s->math + s->english;
    s->average = s->total / 3.0f;
}

int find_index_by_id(const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// === 文件操作 ===

void save_to_file() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("保存文件失败！\n");
        return;
    }
    // 写入数量
    fprintf(fp, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %s %.2f %.2f %.2f %.2f %.2f\n", 
            students[i].id, students[i].name, 
            students[i].c_lang, students[i].math, students[i].english,
            students[i].total, students[i].average);
    }
    fclose(fp);
}

void load_from_file() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return; // 文件不存在则跳过

    if (fscanf(fp, "%d", &count) != 1) {
        count = 0;
        fclose(fp);
        return;
    }

    for (int i = 0; i < count; i++) {
        fscanf(fp, "%s %s %f %f %f %f %f", 
            students[i].id, students[i].name, 
            &students[i].c_lang, &students[i].math, &students[i].english,
            &students[i].total, &students[i].average);
    }
    fclose(fp);
}

// === 功能实现 ===

void input_student() {
    clear_screen();
    if (count >= MAX_STUDENTS) {
        printf("系统已满，无法添加！\n");
        pause_screen();
        return;
    }

    Student s;
    printf("请输入学号: ");
    scanf("%s", s.id);
    
    if (find_index_by_id(s.id) != -1) {
        printf("学号已存在！\n");
        pause_screen();
        return;
    }

    printf("请输入姓名: ");
    scanf("%s", s.name);
    printf("请输入C语言成绩: ");
    scanf("%f", &s.c_lang);
    printf("请输入数学成绩: ");
    scanf("%f", &s.math);
    printf("请输入英语成绩: ");
    scanf("%f", &s.english);

    calculate_score(&s);
    students[count++] = s;

    printf("录入成功！\n");
    pause_screen();
}

void delete_student() {
    clear_screen();
    char id[20];
    printf("请输入要删除的学生学号: ");
    scanf("%s", id);

    int index = find_index_by_id(id);
    if (index == -1) {
        printf("未找到该学生！\n");
    } else {
        // 覆盖删除：将后面的元素前移
        for (int i = index; i < count - 1; i++) {
            students[i] = students[i + 1];
        }
        count--;
        printf("删除成功！\n");
    }
    pause_screen();
}

void modify_student() {
    clear_screen();
    char id[20];
    printf("请输入要修改的学生学号: ");
    scanf("%s", id);

    int index = find_index_by_id(id);
    if (index == -1) {
        printf("未找到该学生！\n");
    } else {
        printf("当前信息: %s %s\n", students[index].id, students[index].name);
        printf("请输入新姓名: ");
        scanf("%s", students[index].name);
        printf("请输入新C语言成绩: ");
        scanf("%f", &students[index].c_lang);
        printf("请输入新数学成绩: ");
        scanf("%f", &students[index].math);
        printf("请输入新英语成绩: ");
        scanf("%f", &students[index].english);
        
        calculate_score(&students[index]);
        printf("修改成功！\n");
    }
    pause_screen();
}

void search_student() {
    clear_screen();
    char id[20];
    printf("请输入要查询的学生学号: ");
    scanf("%s", id);

    int index = find_index_by_id(id);
    if (index == -1) {
        printf("未找到该学生！\n");
    } else {
        printf("\n%-10s %-10s %-8s %-8s %-8s %-8s %-8s\n", "学号", "姓名", "C语言", "数学", "英语", "总分", "平均分");
        printf("------------------------------------------------------------------\n");
        printf("%-10s %-10s %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f\n", 
            students[index].id, students[index].name, 
            students[index].c_lang, students[index].math, students[index].english,
            students[index].total, students[index].average);
    }
    pause_screen();
}

void print_all() {
    clear_screen();
    if (count == 0) {
        printf("暂无学生信息。\n");
    } else {
        printf("%-10s %-10s %-8s %-8s %-8s %-8s %-8s\n", "学号", "姓名", "C语言", "数学", "英语", "总分", "平均分");
        printf("------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            printf("%-10s %-10s %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f\n", 
                students[i].id, students[i].name, 
                students[i].c_lang, students[i].math, students[i].english,
                students[i].total, students[i].average);
        }
    }
    pause_screen();
}

void sort_by_total() {
    clear_screen();
    // 冒泡排序
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].total < students[j + 1].total) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("排序完成 (按总分从高到低)！\n");
    print_all(); // 排序后直接显示
}
