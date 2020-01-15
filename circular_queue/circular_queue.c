//
// Created by ruby on 2020/1/14.
//

/**
 * 循环队列
 */

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 5

typedef int Status;
typedef int ElemType;

typedef struct SqQueue {
    ElemType data[MAXSIZE]; // 队列数据存储的数组
    int front; // 头指针
    int rear;  // 尾指针
} SqQueue;

/**
 * 初始化循环队列
 *
 * @param Q 循环队列
 */
void InitSqQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

/**
 * 进队列
 *
 * @param Q 队列
 * @param e 要进队列的元素
 * @return 1-成功 0-失败
 */
Status EnQueue(SqQueue *Q, ElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        printf("Q is full: EnQueue fails.\n");
        return ERROR;
    }

    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;

    return OK;
}

/**
 * 出队列
 *
 * @param Q 队列
 * @param e 出队列的元素
 * @return 1-成功 0-失败
 */
Status DeQueue(SqQueue *Q, ElemType *e)
{
    if (Q->front == Q->rear) {
        printf("Q is empty: DeQueue fails.\n");
        return ERROR;
    }

    int index = (Q->rear - 1 + MAXSIZE) % MAXSIZE;
    Q->rear = index;
    *e = Q->data[index];

    return OK;
}

/**
 * 返回队列长度
 *
 * @param Q 循环队列
 * @return 队列长度
 */
int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/**
 * 打印循环队列
 *
 * @param Q 循环队列
 */
void dump(SqQueue Q)
{
    if (Q.front == Q.rear) {
        printf("(Q is empty.)\n");
        return;
    }

    printf("Q.front = %d, Q.rear = %d\n", Q.front, Q.rear);

    for (int i = Q.front; i % MAXSIZE < Q.rear; ++i) {
        printf("%d ", Q.data[i]);
    }
    printf("\n");
}

int main()
{
    // 初始化循环队列
    SqQueue Q;
    InitSqQueue(&Q);
    dump(Q);

    // 进循环队列（实际只能存储 4 个数，还有一位做尾指针了）
    printf("进队列:\n");
    EnQueue(&Q, 4);
    EnQueue(&Q, 6);
    EnQueue(&Q, 7);
    EnQueue(&Q, 8);
    EnQueue(&Q, 10);
    dump(Q);

    printf("Q length: %d\n", QueueLength(Q));

    // 出循环队列
    printf("出队列:\n");
    ElemType e;
    DeQueue(&Q, &e);
    printf("DeQueue: %d\n", e);
    dump(Q);

    // 全部数据出队列
    printf("全部数据出队列:\n");
    DeQueue(&Q, &e);
    printf("DeQueue: %d\n", e);
    dump(Q);
    DeQueue(&Q, &e);
    printf("DeQueue: %d\n", e);
    dump(Q);
    DeQueue(&Q, &e);
    printf("DeQueue: %d\n", e);
    dump(Q);

    return 0;
}
