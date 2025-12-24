尝试链接 f1.o 和 f2.o
```bash
gcc obj/f1.o obj/f2.o -o ff.out
```
结果： 会报错。 

原因：C语言程序执行必须有一个入口点，即 main 函数。f1.o 和 f2.o 中都没有 main 函数，所以链接器不知道程序从哪里开始运行，导致链接失败。
