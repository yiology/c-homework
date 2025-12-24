//数组逆序排列

#include <stdio.h>

int main() {
    int a[10];
    int i, temp;

    printf("请输入10个整数：\n");
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }

    // 逆序交换逻辑：只需循环一半长度
    for (i = 0; i < 5; i++) {
        temp = a[i];
        a[i] = a[9 - i];
        a[9 - i] = temp;
    }

    printf("逆序后的数组为：\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
