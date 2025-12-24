预计下列c语言代码的结果

预计结果：

初始: a=5, b=5

a++: 输出 5，然后 a 变成 6。

++b: b 先变成 6，输出 6。

重置: a=8, b=8

a-- + 10: 先算 8 + 10 = 18 (result)，然后 a 变成 7。

--b + 10: b 先变成 7，再算 7 + 10 = 17 (result)。

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = 5;
    int result;

    printf("初始值: a = %d, b = %d\n\n", a, b);

    printf("---- 练习 1: 后置自增 ----\n");
    printf("表达式 a++ 的值是: %d\n", a++);
    printf("执行 a++ 后, a 的值是: %d\n\n", a);

    printf("---- 练习 2: 前置自增 ----\n");
    printf("表达式 ++b 的值是: %d\n", ++b);
    printf("执行 ++b 后, b 的值是: %d\n\n", b);

    a = 8;
    b = 8;
    printf("---- 练习 3: 综合运算 ----\n");
    printf("重置值: a = %d, b = %d\n", a, b);
    
    result = a-- + 10; 
    printf("result = a-- + 10 的结果是: %d\n", result);
    printf("执行后, a 的值是: %d\n\n", a);

    result = --b + 10; 
    printf("result = --b + 10 的结果是: %d\n", result);
    printf("执行后, b 的值是: %d\n\n", b);

    return 0;
}
```
