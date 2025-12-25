//非递归释放链表
//关键点：在销毁当前节点前，必须先保存 next 节点的地址，否则会造成内存丢失。

#include <stdlib.h>

typedef struct list_item {
    int data;
    struct list_item *next;
} list_item;

void erase_list(list_item *head) {
    list_item *current = head;
    list_item *next_node;

    while (current != NULL) {
        next_node = current->next; // 1. 保存下一个
        free(current);             // 2. 释放当前
        current = next_node;       // 3. 移动到下一个
    }
}
