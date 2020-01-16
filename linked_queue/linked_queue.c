//
// Created by ruby on 2020/1/16.
//

/**
 * 链队列
 *
 * 1. 队列空: LinkedQueue->length = 0; LinkedQueue->front = LinkedQueue->rear = NULL;
 * 2. 队列满: 没有满的情况
 */

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

// 链队列节点结构
typedef struct Node {
    ElemType data;     // 节点保存的数据
    struct Node* next; // 下一个节点的指针
} Node;

// 链队列结构
typedef struct LinkedQueue {
    Node* front;  // 队列头
    Node* rear;   // 队列尾
    unsigned int length; // 队列长度
} LinkedQueue;

/**
 * 初始化链队列
 *
 * @param Q 需要初始化的链队列的地址
 */
void InitLinkedQueue(LinkedQueue *Q)
{
    Q->front = NULL;
    Q->rear = NULL;
    Q->length = 0;
}

/**
 * 元素进链队列
 *
 * @param Q 要操作的链队列
 * @param e 要进队列的元素
 * @return 1-成功 0-失败
 */
Status EnQueue(LinkedQueue *Q, ElemType e)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;

    // 队列非空的时候和原有队列链接起来
    if (Q->length > 0) {
        Q->rear->next = node;
    }

    // 插入到队尾
    Q->rear = node;

    // 队列长度增长
    ++Q->length;

    // 队列空的时候，初始化 front 指针
    if (Q->front == NULL) {
        Q->front = Q->rear;
    }

    return OK;
}

/**
 * 元素出链队列
 *
 * @param Q 要操作的链队列
 * @param e 要出队列的元素
 * @return 1-成功 0-失败
 */
Status DeQueue(LinkedQueue *Q, ElemType *e)
{
    if (Q->length == 0) {
        printf("DeQueue fails: queue is empty.\n");
        return ERROR;
    }

    // 出队列头节点
    Node *node = Q->front;
    *e = node->data;

    // 队列头节点指向下一个节点
    Q->front = node->next;

    // 队列长度减 1
    --Q->length;

    // 全部出队了，尾节点也要设置为 NULL
    if (Q->length == 0) {
        Q->rear = NULL;
    }

    return OK;
}

/**
 * 打印链队列
 *
 * @param Q 链队列
 */
void dump(LinkedQueue Q)
{
    if (Q.length == 0) {
        printf("(dump: linked queue is empty.)\n");
        return;
    }

    printf("Queue length: %d\n", Q.length);
    Node *cursor = Q.front;
    while (cursor) {
        if (cursor->next)
            printf("%d -> ", cursor->data);
        else
            printf("%d", cursor->data);

        cursor = cursor->next;
    }
    printf("\n");
}

int main()
{
    printf("Linked queue.\n");

    // 初始化链队列
    LinkedQueue Q;
    InitLinkedQueue(&Q);
    dump(Q);

    // 进队列测试
    EnQueue(&Q, 5);
    EnQueue(&Q, 62);
    EnQueue(&Q, 8);
    EnQueue(&Q, 90);
    dump(Q);

    // 出队列测试
    ElemType e;
    DeQueue(&Q, &e);
    printf("DeQueue: %d\n", e);
    dump(Q);

    DeQueue(&Q, &e);
    printf("DeQueue: %d\n", e);
    dump(Q);

    // 全部出队列
    DeQueue(&Q, &e);
    DeQueue(&Q, &e);
    DeQueue(&Q, &e);
    dump(Q);

    // 重新入队列
    EnQueue(&Q, 11);
    dump(Q);

    return 0;
}

/*
Linked queue.
(dump: linked queue is empty.)
Queue length: 4
5 -> 62 -> 8 -> 90
DeQueue: 5
Queue length: 3
62 -> 8 -> 90
DeQueue: 62
Queue length: 2
8 -> 90
DeQueue fails: queue is empty.
(dump: linked queue is empty.)
Queue length: 1
11
 */
