# 编写 main.c

首先，创建并打开文件：
```bash
touch main.c
vim main.c
```
然后，输入以下代码：
```c
#include <stdio.h>

// 声明外部函数
void f1();
void f2();

int main() {
    // 题目要求：调用printf打印一条信息
    printf("Hello, World! This is my first lab.\n");

    // 调用另外两个函数
    f1();
    f2();

    return 0;
}
```
# 编写 f1.c

创建并打开文件：
```bash
touch f1.c
vim f1.c
```
输入以下代码：
```c
#include <stdio.h>

// 定义函数 f1

void f1() {

    printf("This is function f1.\n");
}
```

# 编写 f2.c
创建并打开文件：
```bash
touch f1.c
vim f1.c
```
输入以下代码：
```c
#include <stdio.h>

// 定义函数 f2

void f2() {

    printf("This is function f2.\n");
}
```
