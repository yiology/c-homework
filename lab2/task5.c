//求 1 到 n 之间的奇数和

#include <stdio.h>

int main() {
    int n;
    long long sum = 0;
    printf("请输入正整数 n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        if (i % 2 != 0) {
            sum += i;
        }
    }

    printf("1 到 %d 之间的奇数和为: %lld\n", n, sum);
    return 0;
}
