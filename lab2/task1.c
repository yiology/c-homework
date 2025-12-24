//输出每个月的天数

#include <stdio.h>

int main() {
    int year;
    printf("请输入年份: ");
    scanf("%d", &year);

    // 判断闰年逻辑
    int is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    printf("%d 年各月天数如下：\n", year);
    for (int month = 1; month <= 12; month++) {
        int days;
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                days = 31;
                break;
            case 4: case 6: case 9: case 11:
                days = 30;
                break;
            case 2:
                days = is_leap ? 29 : 28;
                break;
            default:
                days = 0;
        }
        printf("%2d月: %d 天\n", month, days);
    }
    return 0;
}
