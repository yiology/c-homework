//内存补全挑战

#include <stdio.h>

int main() {
    // "C!YYDS!" 加上末尾的 '\0' 刚好 8 个字节
    // 我们可以直接通过指针转换来打印
    long x = 0x21534459592143; // 对应 ASCII: C ! Y Y D S ! \0 (小端序逆序)
    
    // 补全代码：将 &x 强制转换为 char* 类型
    printf("%s\n", (char *)&x);
    
    return 0;
}
