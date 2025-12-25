//电影院选座购票系统


#include <stdio.h>
#include <stdlib.h>

// === 配置 ===
#define ROWS 10             // 行数
#define COLS 10             // 列数
#define PRICE 45            // 票价 (元)
#define DATA_FILE "cinema_data.txt" // 数据存储文件

// 全局变量：座位数组 (0表示空, 1表示已售)
int seats[ROWS][COLS];

// === 函数声明 ===
void load_data();
void save_data();
void display_seats();
void book_seat();
void clear_screen();
void pause_screen();

int main() {
    // 1. 程序启动时，先加载数据
    load_data();

    int choice;
    while (1) {
        clear_screen();
        printf("===================================\n");
        printf("      🎬 电影院选座系统 v1.0\n");
        printf("===================================\n");
        printf("  1. 显示座位图\n");
        printf("  2. 选座购票\n");
        printf("  0. 退出系统\n");
        printf("===================================\n");
        printf("请输入选项: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // 清除错误输入
            continue;
        }

        switch (choice) {
            case 1:
                display_seats();
                pause_screen();
                break;
            case 2:
                display_seats(); // 选座前先看一眼
                book_seat();
                pause_screen();
                break;
            case 0:
                // 退出前不需要手动保存，因为购票成功时已经实时保存了
                // 但为了保险，也可以在这里调用 save_data();
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("无效选项！\n");
                pause_screen();
        }
    }
    return 0;
}

// === 核心功能 ===

// 1. 加载数据 (持久化读取)
void load_data() {
    FILE *fp = fopen(DATA_FILE, "r");
    
    // 如果文件不存在（第一次运行），则初始化为全空
    if (fp == NULL) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                seats[i][j] = 0;
            }
        }
        return;
    }

    // 从文件读取状态
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fscanf(fp, "%d", &seats[i][j]);
        }
    }
    fclose(fp);
}

// 2. 保存数据 (持久化写入)
void save_data() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("错误：无法保存数据！\n");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(fp, "%d ", seats[i][j]);
        }
        fprintf(fp, "\n"); // 每一行换个行，方便人类阅读文件
    }
    fclose(fp);
}

// 3. 展示座位
void display_seats() {
    printf("\n       ======= 荧幕 =======\n\n");
    
    // 打印列号
    printf("     ");
    for (int j = 1; j <= COLS; j++) {
        printf("%d ", j); // 打印列头 1 2 3...
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        // 打印行号 (为了对齐，小于10加个空格)
        printf("第%2d行 ", i + 1);
        
        for (int j = 0; j < COLS; j++) {
            if (seats[i][j] == 0) {
                // 空座 (使用 Unicode 方块)
                printf("\033[37m□ \033[0m"); 
            } else {
                // 已售 (红色实心方块)
                printf("\033[31m■ \033[0m"); 
            }
        }
        printf("\n");
    }
    printf("\n图例: □ 空座  \033[31m■ 已售\033[0m\n");
}

// 4. 选座购票
void book_seat() {
    int r, c;
    printf("\n请输入座位的行列号 (格式: 行 列): ");
    
    if (scanf("%d %d", &r, &c) != 2) {
        while(getchar() != '\n');
        printf("❌ 输入格式错误！\n");
        return;
    }

    // 检查边界
    if (r < 1 || r > ROWS || c < 1 || c > COLS) {
        printf("❌ 座位不存在！行(1-%d), 列(1-%d)\n", ROWS, COLS);
        return;
    }

    // 转换为数组下标 (用户输入1，数组是0)
    int row_idx = r - 1;
    int col_idx = c - 1;

    // 检查是否已被占用
    if (seats[row_idx][col_idx] == 1) {
        printf("❌ 该座位 [ %d行%d列 ] 已被售出，请重新选择。\n", r, c);
    } else {
        // 执行购票
        seats[row_idx][col_idx] = 1;
        printf("\n✅ 购票成功！\n");
        printf("座位: 第 %d 行 第 %d 列\n", r, c);
        printf("票价: %d 元\n", PRICE);
        
        // **关键点：购票后立刻保存，防止异常退出导致数据丢失**
        save_data(); 
        printf("(系统已自动保存数据)\n");
    }
}

// === 辅助工具 ===
void clear_screen() {
    printf("\033[H\033[J"); // Linux/Mac 清屏指令
}

void pause_screen() {
    printf("\n按回车键返回菜单...");
    getchar(); getchar(); 
}
