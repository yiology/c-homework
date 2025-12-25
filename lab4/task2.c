//指针遍历数组

#include <stdio.h>

int main() {
    int a[5];
    int *p = a; // 指向数组首元素

    printf("请输入 5 个整数：\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", p + i);
    }

    printf("\n元素值与地址列表：\n");
    for (int i = 0; i < 5; i++) {
        // 使用指针算术运算访问
        printf("a[%d] = %d \t 地址: %p\n", i, *(p + i), (void*)(p + i));
    }

    return 0;
}
