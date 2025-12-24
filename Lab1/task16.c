//四则运算
#include <stdio.h>

int main() {
    int num1, num2;

    printf("请输入2个正整数 (用空格隔开): ");
    scanf("%d %d", &num1, &num2);

    printf("和: %d\n", num1 + num2);
    printf("差: %d\n", num1 - num2);
    printf("积: %d\n", num1 * num2);
    
    // 整数除法会丢弃小数。如果除数为0会崩溃
    if(num2 != 0) {
        printf("商: %d\n", num1 / num2);
    } else {
        printf("商: 除数不能为0\n");
    }

    return 0;
}
