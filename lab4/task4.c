//编写 my_strlen

#include <stdio.h>

int my_strlen(char *str) {
    int count = 0;
    while (*str != '\0') {
        count++;
        str++; // 指针后移
    }
    return count;
}

int main() {
    char s[100];
    printf("请输入一个字符串: ");
    scanf("%s", s);

    printf("字符串长度为: %d\n", my_strlen(s));
    return 0;
}
