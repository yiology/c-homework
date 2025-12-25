//函数指针传参交换变量

#include <stdio.h>

// 交换函数：接收地址
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a, b;
    printf("请输入两个整数: ");
    scanf("%d %d", &a, &b);

    printf("交换前: a = %d, b = %d\n", a, b);
    swap(&a, &b); // 传入地址
    printf("交换后: a = %d, b = %d\n", a, b);

    return 0;
}
