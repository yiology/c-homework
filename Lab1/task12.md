运行以下命令查看反汇编代码：
```Bash
objdump -d ~/main.out | grep -E "main>|f1>|f2>"
```
看到输出中包含 main、f1 和 f2 的段落，就证明这三个函数的代码都被链接进去了。
