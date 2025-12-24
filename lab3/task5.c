// 自定义二维数组访问函数

#include <stdio.h>

/**
 * 核心公式：目标地址 = 基准地址 + (目标行 - 基准行) * 总列数 + (目标列 - 基准列)
 */
int two_dim_array_access(int *x, int i, int j, int m, int n, int C) {
    // x 是 A[i][j] 的地址
    // m, n 是目标下标
    // C 是第二维的大小（总列数）
    return *(x + (m - i) * C + (n - j));
}

int main() {
    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};

    // 验证逻辑
    printf("测试 1: %d (预期 6)\n", two_dim_array_access(&A[0][0], 0, 0, 1, 2, 3));
    printf("测试 2: %d (预期 6)\n", two_dim_array_access(&A[0][1], 0, 1, 1, 2, 3));

    return 0;
}
