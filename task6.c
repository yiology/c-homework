//字符二维数组排序

//先对每一行内部进行排序（升序）。
//计算每一行的 ASCII 总和。
//根据总和对整行进行排序。

#include <stdio.h>

void sort_row(char row[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (row[j] > row[j+1]) {
                char t = row[j]; row[j] = row[j+1]; row[j+1] = t;
            }
        }
    }
}

int main() {
    char A[5][6] = {
        {'S','D','U','Y','E','S'},
        {'C','H','I','N','A','!'},
        {'A','F','T','E','R','X'},
        {'h','e','r','o','a','b'},
        {'C','y','y','D','S','!'}
    };

    // 1. 先把每一行内部排好序
    for (int i = 0; i < 5; i++) {
        sort_row(A[i], 6);
    }

    // 2. 根据每行 ASCII 和进行行间排序（冒泡）
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            int sum1 = 0, sum2 = 0;
            for (int k = 0; k < 6; k++) {
                sum1 += A[j][k];
                sum2 += A[j+1][k];
            }
            if (sum1 > sum2) {
                // 交换整行
                for (int k = 0; k < 6; k++) {
                    char temp = A[j][k];
                    A[j][k] = A[j+1][k];
                    A[j+1][k] = temp;
                }
            }
        }
    }

    // 打印结果
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) printf("'%c' ", A[i][j]);
        printf("\n");
    }

    return 0;
}
