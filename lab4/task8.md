# 多模块编译与头文件

## 文件 1: module.h (头文件)

```c
#ifndef MODULE_H
#define MODULE_H

extern int global_var; // 声明全局变量
int func1();           // 声明函数
int func2();

#endif
```
## 文件 2: main.c (调用)

```c
#include <stdio.h>
#include "module.h"

int main() {
    printf("函数1返回值: %d\n", func1());
    printf("函数2返回值: %d\n", func2());
    printf("全局变量值: %d\n", global_var);
    return 0;
}
```

## 编译与运行流程

第一步：编译 main.c 并将它与 module.o 链接在一起
```bash
gcc main.c module.o -o lab4_task8
```
第二步：运行生成的可执行程序
```bash
./lab4_task8
```
