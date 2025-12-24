//统计数字出现次数

#include <stdio.h>

int main() {
    int input[10];
    int count[10] = {0}; // 初始化为0，用于统计 0-9 的频率
    int i;

    printf("请输入10个0-9之间的整数：\n");
    for (i = 0; i < 10; i++) {
        scanf("%d", &input[i]);
        if (input[i] >= 0 && input[i] <= 9) {
            count[input[i]]++; // 数字即下标，计数自增
        }
    }

    printf("\n统计结果：\n");
    for (i = 0; i < 10; i++) {
        printf("数字 %d 出现了 %d 次\n", i, count[i]);
    }

    return 0;
}
