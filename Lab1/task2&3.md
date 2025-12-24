# 编写 main.c

touch main.c 

vim main.c

#include <stdio.h>

// 声明外部函数，告诉编译器这两个函数在别的地方定义了

void f1();

void f2();

int main() {

    // 题目要求：调用printf打印一条信息
    
    printf("Hello, World! This is my first lab.\n");
    
    // 调用另外两个函数（虽然题目没强制要求调用，但这样更符合逻辑）
    
    f1();
    
    f2();
    
    return 0;
}

# 编写 f1.c

touch f1.c

vim f1.c

#include <stdio.h>

// 定义函数 f1

void f1() {

    printf("This is function f1.\n");
}

# 编写 f2.c

touch f2.c

vim f2.c

#include <stdio.h>

// 定义函数 f2

void f2() {

    printf("This is function f2.\n");
}

