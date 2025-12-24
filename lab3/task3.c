//选择排序与冒泡排序

#include <stdio.h>

// 冒泡排序：两两比较，大的往后沉
void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

// 选择排序：每次选出最小的放在前面
void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        int temp = a[i];
        a[i] = a[min_idx];
        a[min_idx] = temp;
    }
}

int main() {
    int data1[5] = {5, 3, 8, 1, 2};
    int data2[5] = {5, 3, 8, 1, 2};

    bubble_sort(data1, 5);
    selection_sort(data2, 5);

    printf("冒泡排序结果：");
    for(int i=0; i<5; i++) printf("%d ", data1[i]);
    
    printf("\n选择排序结果：");
    for(int i=0; i<5; i++) printf("%d ", data2[i]);
    printf("\n");

    return 0;
}
