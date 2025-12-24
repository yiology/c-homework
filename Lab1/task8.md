创建并打开文件
```bash
touch main2.c
vim main2.c
```
输入代码
```c
#include <stdio.h>

int main() {
    printf("Hello, World from main2!\n");
    return 0;
}
```

编译
```bash
gcc -c src/main2.c -o obj/main2.o
```
