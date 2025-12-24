尝试链接所有 .o 文件
```Bash
gcc obj/main.o obj/main2.o obj/f1.o obj/f2.o -o new.all.out
```
结果：会报错。 
原因：一个可执行程序只能有一个 main 函数。main.o 和 main2.o 里面都定义了 main 函数，链接器不知道该使用哪一个，发生冲突。
