# 创建代码

touch main2.c

vim main2.c

#include <stdio.h>

int main() {
    printf("Hello, World from main2!\n");
    return 0;
}


# 编译

gcc -c src/main2.c -o obj/main2.o
