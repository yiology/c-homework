//指针基础操作

#include <stdio.h>

int main() {
    int a = 10, b = 20;
    int *p;

    // (1) 指针 p 指向 a
    p = &a;

    // (2) 输出 a 的值、地址、p 的值、*p 的值
    printf("a 的值: %d\n", a);
    printf("a 的地址: %p\n", (void*)&a);
    printf("p 的值 (a 的地址): %p\n", (void*)p);
    printf("*p 的值 (a 的值): %d\n", *p);

    // (3) 让 p 指向 b，修改 b 的值为 *p + 10
    p = &b;
    *p = *p + 10; // 此时 *p 就是 b

    // (4) 输出修改后的 b
    printf("\n修改后的 b 的值: %d\n", b);

    return 0;
}
