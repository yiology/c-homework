//万年历程序设计 (任务 1, 2, 3)
//为了代码的整洁和复用，我将这三个功能整合进了一个模块化的程序中。它包含了判断闰年、计算月份天数、计算星期以及打印日历的核心逻辑。

#include <stdio.h>

// --- 工具函数 ---

// 判断是否为闰年
int is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// 获取某年某月的天数
int get_days_in_month(int y, int m) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && is_leap(y)) return 29;
    return days[m - 1];
}

// 计算从公元 1 年 1 月 1 日到指定日期的总天数
// 我们先算出一个绝对天数，再利用 2025-11-12 是周三来对齐
long get_total_days(int y, int m, int d) {
    long total = 0;
    for (int i = 1; i < y; i++) {
        total += is_leap(i) ? 366 : 365;
    }
    for (int i = 1; i < m; i++) {
        total += get_days_in_month(y, i);
    }
    total += d;
    return total;
}

// 核心功能 1：判断星期几
// 基准：2025-11-12 是周三
int get_weekday(int y, int m, int d) {
    long ref_days = get_total_days(2025, 11, 12);
    long target_days = get_total_days(y, m, d);
    long diff = target_days - ref_days;
    
    // (周三是3 + 偏移量) % 7
    int w = (3 + (diff % 7) + 7) % 7; 
    return (w == 0) ? 7 : w; // 返回 1-7 代表周一到周日
}

// 核心功能 2：打印单月日历
void print_month_calendar(int y, int m) {
    char *months[] = {"January", "February", "March", "April", "May", "June", 
                      "July", "August", "September", "October", "November", "December"};
    printf("\n  ------------ %s %d ------------\n", months[m-1], y);
    printf("  Mon  Tue  Wed  Thu  Fri  Sat  Sun\n");

    int start_wh = get_weekday(y, m, 1);
    int days = get_days_in_month(y, m);

    // 打印开头的空格
    for (int i = 1; i < start_wh; i++) printf("     ");

    for (int d = 1; d <= days; d++) {
        printf("%5d", d);
        if ((start_wh + d - 1) % 7 == 0) printf("\n");
    }
    printf("\n");
}

// --- 主函数 ---

int main() {
    int choice, y, m, d;
    printf("1. 查询特定日子星期几\n2. 打印特定月份日历\n3. 打印全年万年历\n请选择: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("输入年 月 日: ");
        scanf("%d %d %d", &y, &m, &d);
        int w = get_weekday(y, m, d);
        printf("该日是星期 %d\n", w);
    } 
    else if (choice == 2) {
        printf("输入年 月: ");
        scanf("%d %d", &y, &m);
        print_month_calendar(y, m);
    } 
    else if (choice == 3) {
        printf("输入年份: ");
        scanf("%d", &y);
        for (int i = 1; i <= 12; i++) {
            print_month_calendar(y, i);
        }
    }

    return 0;
}
