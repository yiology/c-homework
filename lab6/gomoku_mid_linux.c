//作业任务
//1.请编程实现五子棋双人对战的版本。
//2.请为上述五子棋实现一个智能体，可以人机大战。
//我将两个任务放在了一起完成


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// === 基础配置 ===
#define SIZE 15
#define EMPTY 0
#define BLACK 1 // 玩家 (X)
#define WHITE 2 // 电脑 (O)

int board[SIZE][SIZE];

// === 评分权重 ===
// 只要权重设置合理，不用搜索算法也能达到不错的水准
#define WIN5        100000 // 连五 (最高优先级)
#define LIVE4       10000  // 活四 (011110) - 下一步必胜
#define DEAD4       1000   // 冲四 (211110) - 必须堵或必须连
#define LIVE3       1000   // 活三 (01110)  - 很好的进攻点
#define DEAD3       100    // 眠三
#define LIVE2       100    // 活二
#define DEAD2       10     // 眠二

// === 函数声明 ===
void init_board();
void print_board();
void clear_screen();
bool place_piece(int r, int c, int p);
bool check_win(int r, int c, int p);
int  evaluate_point(int r, int c, int player);
void computer_move();

// === 主程序 ===
int main() {
    int row, col;
    int current_player = BLACK; // 玩家黑棋先手
    bool game_over = false;

    init_board();
    srand(time(NULL)); // 随机种子

    clear_screen();
    printf("\n=== 五子棋 (中级挑战版) ===\n");
    printf("难度: 中等 (会防守，懂进攻，但没有长远算计)\n");
    printf("你是黑棋 [X]，AI 是白棋 [O]\n");
    printf("输入坐标格式: 行 列 (例如: 8 8)\n");
    printf("随时输入 0 0 退出游戏\n\n");

    print_board();

    while (!game_over) {
        if (current_player == BLACK) {
            // --- 玩家回合 ---
            printf("\n轮到你 [黑棋 X] (输入 0 0 退出): ");
            
            int result = scanf("%d %d", &row, &col);
            
            // 输入验证
            if (result != 2) {
                while(getchar() != '\n');
                printf("❌ 输入无效，请输入数字。\n");
                continue;
            }

            // 退出检测
            if (row == 0 && col == 0) {
                printf("已退出游戏。再见！\n");
                return 0;
            }

            row--; col--; // 坐标转换

            if (!place_piece(row, col, current_player)) {
                printf("❌ 位置无效，请重试。\n");
                continue;
            }

            if (check_win(row, col, BLACK)) {
                print_board();
                printf("\n🎉 恭喜！你战胜了中级 AI！\n");
                game_over = true;
            }
        } else {
            // --- 电脑回合 ---
            printf("\n🤖 AI 正在思考...\n");
            
            // 简单的延时，让游戏节奏不要太快
            // (实际计算只需 0.01秒，加上延时模拟思考感)
            
            computer_move();
            
            // 检查电脑是否获胜
            // (为了简化代码，这里用简单的全盘扫描)
            for(int i=0; i<SIZE; i++) {
                for(int j=0; j<SIZE; j++) {
                    if(board[i][j] == WHITE && check_win(i, j, WHITE)) {
                        print_board();
                        printf("\n💀 遗憾，AI 获胜了。\n");
                        game_over = true;
                        goto end_loop;
                    }
                }
            }
        }

        if (!game_over) {
            print_board();
            current_player = (current_player == BLACK) ? WHITE : BLACK;
        }
    }

    end_loop:
    return 0;
}

// === 界面与基础逻辑 ===

void init_board() {
    for(int i=0; i<SIZE; i++) for(int j=0; j<SIZE; j++) board[i][j] = EMPTY;
}

void clear_screen() {
    printf("\033[H\033[J"); // ANSI 转义码清屏
}

void print_board() {
    clear_screen();
    printf("\n   ");
    for(int i=1; i<=SIZE; i++) printf("%2d ", i);
    printf("\n");
    for(int i=0; i<SIZE; i++) {
        printf("%2d ", i+1);
        for(int j=0; j<SIZE; j++) {
            if(board[i][j] == BLACK) printf("\033[32m X \033[0m"); // 绿X
            else if(board[i][j] == WHITE) printf("\033[31m O \033[0m"); // 红O
            else printf(" + ");
        }
        printf("\n");
    }
}

bool place_piece(int r, int c, int p) {
    if(r<0 || r>=SIZE || c<0 || c>=SIZE || board[r][c]!=EMPTY) return false;
    board[r][c] = p;
    return true;
}

// 胜利检测
bool check_win(int r, int c, int p) {
    int dirs[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    for(int i=0; i<4; i++) {
        int count = 1;
        for(int k=1; k<=4; k++) {
            int nr=r+k*dirs[i][0], nc=c+k*dirs[i][1];
            if(nr>=0&&nr<SIZE&&nc>=0&&nc<SIZE&&board[nr][nc]==p) count++; else break;
        }
        for(int k=1; k<=4; k++) {
            int nr=r-k*dirs[i][0], nc=c-k*dirs[i][1];
            if(nr>=0&&nr<SIZE&&nc>=0&&nc<SIZE&&board[nr][nc]==p) count++; else break;
        }
        if(count >= 5) return true;
    }
    return false;
}

// === AI 核心 ===

// 计算某个点对于某位玩家的价值分数
int evaluate_point(int r, int c, int player) {
    int total_score = 0;
    int dirs[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};

    // 模拟在这个位置落子
    // 注意：这里不修改 board，只是假设
    // 为了计算准确，我们需要看这个点能连成什么样
    
    for(int k=0; k<4; k++) {
        int count = 1; // 当前这一子
        int open_ends = 0; // 两端是否是空的
        
        // 正向延伸
        int step = 1;
        while(true) {
            int nr = r + step * dirs[k][0];
            int nc = c + step * dirs[k][1];
            if(nr>=0 && nr<SIZE && nc>=0 && nc<SIZE && board[nr][nc] == player) {
                count++;
                step++;
            } else {
                // 检查端点是否为空
                if(nr>=0 && nr<SIZE && nc>=0 && nc<SIZE && board[nr][nc] == EMPTY) open_ends++;
                break;
            }
        }
        
        // 反向延伸
        step = 1;
        while(true) {
            int nr = r - step * dirs[k][0];
            int nc = c - step * dirs[k][1];
            if(nr>=0 && nr<SIZE && nc>=0 && nc<SIZE && board[nr][nc] == player) {
                count++;
                step++;
            } else {
                if(nr>=0 && nr<SIZE && nc>=0 && nc<SIZE && board[nr][nc] == EMPTY) open_ends++;
                break;
            }
        }

        // 根据连子情况打分
        if (count >= 5) total_score += WIN5;
        else if (count == 4) {
            if (open_ends == 2) total_score += LIVE4;
            else if (open_ends == 1) total_score += DEAD4;
        } else if (count == 3) {
            if (open_ends == 2) total_score += LIVE3;
            else if (open_ends == 1) total_score += DEAD3;
        } else if (count == 2) {
            if (open_ends == 2) total_score += LIVE2;
            else if (open_ends == 1) total_score += DEAD2;
        }
    }
    return total_score;
}

void computer_move() {
    // 1. 开局天元 (如果中间是空的)
    if (board[7][7] == EMPTY) {
        // 只有当棋盘上棋子很少时才抢天元，避免中盘抢
        int pieces = 0;
        for(int i=0;i<SIZE;i++) for(int j=0;j<SIZE;j++) if(board[i][j]!=EMPTY) pieces++;
        if(pieces < 2) {
            board[7][7] = WHITE; return;
        }
    }

    int best_score = -1;
    int best_r = -1, best_c = -1;

    // 2. 遍历所有空位
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != EMPTY) continue;

            // 核心逻辑：综合评分 = 进攻分 + 防守分
            // 进攻分：我下这能得多少分？
            int attack_score = evaluate_point(i, j, WHITE);
            
            // 防守分：如果我不下这，让对手下这，他能得多少分？
            int defense_score = evaluate_point(i, j, BLACK);

            // 中级 AI 的特点：攻守兼备，但没有长远算计
            // 稍微偏向进攻 (1.0 : 1.0)，或者稍微偏向防守
            // 这里如果防守分很高（比如对手有活四），必须优先堵
            
            // 特殊逻辑：如果自己能赢，直接下，不用管对手
            if (attack_score >= WIN5) {
                board[i][j] = WHITE; return;
            }
            // 特殊逻辑：如果对手下步能赢 (连5或活4)，必须堵，分值给极大
            if (defense_score >= WIN5 || defense_score >= LIVE4) {
                defense_score = WIN5 - 1; // 仅次于自己赢
            }

            int current_score = attack_score + defense_score;

            // 增加一点随机性，避免 AI 每次都走得一模一样
            // 只有在分数非常接近时才随机
            if (current_score > best_score) {
                best_score = current_score;
                best_r = i;
                best_c = j;
            } else if (current_score == best_score) {
                if (rand() % 2 == 0) {
                    best_r = i;
                    best_c = j;
                }
            }
        }
    }

    // 3. 落子
    if (best_r != -1) {
        board[best_r][best_c] = WHITE;
    } else {
        // 兜底：如果没地方下（几乎不可能）
        for(int i=0; i<SIZE; i++) for(int j=0; j<SIZE; j++) 
            if(board[i][j]==EMPTY) { board[i][j]=WHITE; return; }
    }
}
