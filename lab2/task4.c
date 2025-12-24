//求 1 到 n 的累加和 

#include <stdio.h>

int main() {
    int n;
    long long sum = 0; // 使用 long long 防止 n 较大时溢出
    printf("请输入正整数 n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    printf("1 到 %d 的和为: %lld\n", n, sum);
    return 0;
}
