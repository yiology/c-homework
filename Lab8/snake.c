//贪吃蛇

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

// === 游戏配置 ===
#define WIDTH 40
#define HEIGHT 20

// 每一帧的总时长 (200ms = 0.2秒)
// 蛇移动的速度由此决定
#define FRAME_TIME_US 200000 

// 输入检测的间隔 (10ms)
// 意味着每 0.01 秒就会检测一次键盘，手感极快
#define POLL_INTERVAL_US 10000

enum Direction { UP, DOWN, LEFT, RIGHT };

typedef struct SnakeNode {
    int x;
    int y;
    struct SnakeNode *next;
} SnakeNode;

SnakeNode *head = NULL;
int food_x, food_y;
int score = 0;
int dir = RIGHT;
int next_dir = RIGHT; // 新增：缓存用户的输入
bool game_over = false;

// === 终端设置 ===
void set_terminal_mode(int enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    }
}

int kbhit(void) {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

// === 链表操作 ===
SnakeNode* create_node(int x, int y) {
    SnakeNode* new_node = (SnakeNode*)malloc(sizeof(SnakeNode));
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    return new_node;
}

void add_head(int x, int y) {
    SnakeNode* new_node = create_node(x, y);
    new_node->next = head;
    head = new_node;
}

void remove_tail() {
    if (head == NULL || head->next == NULL) return;
    SnakeNode* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

bool is_on_snake(int x, int y) {
    SnakeNode* current = head;
    while (current != NULL) {
        if (current->x == x && current->y == y) return true;
        current = current->next;
    }
    return false;
}

void free_snake() {
    SnakeNode* current = head;
    while (current != NULL) {
        SnakeNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// === 游戏逻辑 ===
void generate_food() {
    do {
        food_x = (rand() % (WIDTH - 2)) + 1;
        food_y = (rand() % (HEIGHT - 2)) + 1;
    } while (is_on_snake(food_x, food_y));
}

void init_game() {
    int start_x = WIDTH / 2;
    int start_y = HEIGHT / 2;
    
    // 正确的初始化顺序：先尾后头
    head = create_node(start_x - 2, start_y);
    add_head(start_x - 1, start_y);
    add_head(start_x, start_y);
    
    dir = RIGHT;
    next_dir = RIGHT;
    generate_food();
}

void draw() {
    printf("\033[H\033[?25l"); 
    for (int i = 0; i < WIDTH; i++) printf("#");
    printf("\n");

    for (int y = 1; y < HEIGHT - 1; y++) {
        printf("#");
        for (int x = 1; x < WIDTH - 1; x++) {
            if (x == head->x && y == head->y) {
                printf("\033[32m@\033[0m"); 
            } else if (x == food_x && y == food_y) {
                printf("\033[31m*\033[0m"); 
            } else if (is_on_snake(x, y)) {
                printf("o");
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH; i++) printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

// 优化后的输入处理
void input() {
    if (kbhit()) {
        char ch = getchar();
        // 我们修改 next_dir 而不是直接修改 dir
        // 这样在一个移动周期内多次按键，会保留最后一次有效的意图
        // 并且防止 "快速反向自杀" (例如当前向右，快速按上、左，导致还没移动就撞死)
        switch (ch) {
            case 'w': if (dir != DOWN) next_dir = UP; break;
            case 's': if (dir != UP) next_dir = DOWN; break;
            case 'a': if (dir != RIGHT) next_dir = LEFT; break;
            case 'd': if (dir != LEFT) next_dir = RIGHT; break;
            case 'q': game_over = true; break;
        }
    }
}

void logic() {
    // 每一帧真正移动前，更新方向
    dir = next_dir;

    int new_x = head->x;
    int new_y = head->y;

    switch (dir) {
        case UP:    new_y--; break;
        case DOWN:  new_y++; break;
        case LEFT:  new_x--; break;
        case RIGHT: new_x++; break;
    }

    if (new_x <= 0 || new_x >= WIDTH - 1 || new_y <= 0 || new_y >= HEIGHT - 1) {
        game_over = true;
        return;
    }

    if (is_on_snake(new_x, new_y)) {
        game_over = true;
        return;
    }

    add_head(new_x, new_y);

    if (new_x == food_x && new_y == food_y) {
        score += 10;
        generate_food();
    } else {
        remove_tail();
    }
}

int main() {
    srand(time(NULL));
    
    printf("\033[2J\033[H");
    printf("=== 丝滑版贪吃蛇 ===\n按回车键开始...\n");
    getchar(); 

    set_terminal_mode(1);
    init_game();

    // 绘制初始画面
    draw();

    while (!game_over) {
        // === 核心修改：时间切片 ===
        // 蛇移动一次需要 FRAME_TIME_US (比如 200ms)
        // 我们把它切成很多个 10ms 的小片段
        // 在每个小片段里都检查输入
        
        int time_elapsed = 0;
        while (time_elapsed < FRAME_TIME_US) {
            input(); // 高频检测输入
            usleep(POLL_INTERVAL_US); // 只睡一小会儿 (10ms)
            time_elapsed += POLL_INTERVAL_US;
            
            // 如果玩家按了退出，立刻跳出
            if (game_over) break;
        }

        if (game_over) break;

        // 时间到了，移动蛇
        logic();
        draw();
    }

    set_terminal_mode(0);
    printf("\033[?25h");
    printf("\nGame Over! Score: %d\n", score);
    free_snake();
    return 0;
}
