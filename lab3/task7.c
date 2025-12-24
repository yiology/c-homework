//矩阵乘法
//矩阵乘法的经典实现：C[i][j] 等于 A 的第 i 行与 B 的第 j 列的对应元素乘积之和。

#include <stdio.h>

void matrix_multi(double A[3][4], double B[4][5], double C[3][5]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            C[i][j] = 0; // 初始化
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // 这里简单初始化 A 和 B 用于测试
    double A[3][4] = {{1,1,1,1}, {1,1,1,1}, {1,1,1,1}};
    double B[4][5] = {{1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}};
    double C[3][5];

    matrix_multi(A, B, C);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) printf("%.1f ", C[i][j]);
        printf("\n");
    }

    return 0;
}
