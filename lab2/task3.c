// 字符的二进制位拆解

#include <stdio.h>

int main() {
    char ch;
    printf("请输入一个字符: ");
    scanf(" %c", &ch); // 前面的空格用于跳过可能的回车符

    // 格式化输出，从高位 (第8位) 到低位 (第1位)
    // 使用位移运算 >> 和位与运算 &
    printf("The eighth bit is %d,\n", (ch >> 7) & 1);
    printf("The seventh bit is %d,\n", (ch >> 6) & 1);
    printf("The sixth bit is %d,\n", (ch >> 5) & 1);
    printf("The fifth bit is %d,\n", (ch >> 4) & 1);
    printf("The fourth bit is %d,\n", (ch >> 3) & 1);
    printf("The third bit is %d,\n", (ch >> 2) & 1);
    printf("The second bit is %d,\n", (ch >> 1) & 1);
    printf("The first bit is %d.\n", (ch >> 0) & 1);

    return 0;
}
