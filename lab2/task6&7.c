//素数判断与范围筛选

#include <stdio.h>
#include <stdbool.h>

// 判断是否为素数的函数
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) { // 只需检查到根号n
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int x;
    printf("请输入一个较大的正数 x: ");
    scanf("%d", &x);

    // 题目 6: 判断单个值
    printf("判断 %d 是否为素数: %s\n", x, is_prime(x) ? "yes" : "no");

    // 题目 7: 打印范围内的所有素数
    printf("[1, %d] 范围内的素数有:\n", x);
    int count = 0;
    for (int i = 1; i <= x; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
            count++;
            if (count % 10 == 0) printf("\n"); // 每行打印10个，更整齐
        }
    }
    printf("\n");
    return 0;
}
