## 编译与链接实验 (Task 1-12)

通过 gcc -c 指令将源码编译为目标文件，并使用 gcc -o 进行链接。

编译
```bash
gcc -c src/main.c -o obj/main.o
gcc -c src/f1.c -o obj/f1.o
gcc -c src/f2.c -o obj/f2.o
```
链接
```bash
gcc obj/main.o obj/f1.o obj/f2.o -o bin/all.out
```
## C 语言基础编程 (Task 13-18)
本项目在 src/ 目录下实现了以下编程任务：

| 文件名 | 功能描述 |
| :--- | :--- |
| `task13.c` | 输出 int, char 等基本类型的字节数| 
| `task14.c` | 在屏幕输出带有双引号的句子 | 
| `task15.c` | 格式化输出,打印特定排列的倒三角星号图案 |
| `task16.c` | 算术运算,输入两数，计算其和、差、积、商 | 
| `task17.c` |数据类型转换,华氏温度与摄氏温度的数学转换公式实现 |
| `task18.md` | 自增/自减,验证 i++ (先用后加) 与 ++i (先加后用) 的区别 |

---


*Last updated: 2025-12-25*
