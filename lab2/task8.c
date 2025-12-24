//整数反转

#include <stdio.h>

int main() {
    int num, reversed = 0;
    printf("请输入一个整数: ");
    scanf("%d", &num);

    int temp = num;
    while (temp != 0) {
        int digit = temp % 10;
        reversed = reversed * 10 + digit;
        temp /= 10;
    }

    printf("反转后的结果是: %d\n", reversed);
    return 0;
}
