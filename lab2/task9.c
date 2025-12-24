//打印菱形图案

#include <stdio.h>

int main() {
    int n;
    printf("请输入菱形的高度 n (必须为奇数): ");
    scanf("%d", &n);

    if (n % 2 == 0) {
        printf("错误：请输入奇数。\n");
        return 1;
    }

    int mid = n / 2 + 1;

    // 上半部分 (包括中间行)
    for (int i = 1; i <= mid; i++) {
        // 打印空格
        for (int j = 1; j <= mid - i; j++) printf(" ");
        // 打印星号
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }

    // 下半部分
    for (int i = mid - 1; i >= 1; i--) {
        // 打印空格
        for (int j = 1; j <= mid - i; j++) printf(" ");
        // 打印星号
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }

    return 0;
}
