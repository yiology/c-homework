//求三个数的最小值

#include <stdio.h>

int main() {
    int a, b, c, min;
    printf("请输入三个整数 (空格隔开): ");
    scanf("%d %d %d", &a, &b, &c);

    min = a; // 先假设第一个最小
    if (b < min) min = b;
    if (c < min) min = c;

    printf("最小的数是: %d\n", min);
    return 0;
}
