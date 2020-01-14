//
// Created by ruby on 2020/1/14.
//

/**
 * 栈
 *
 * 两栈共享存储空间。使用场景: 两个栈的总长度固定。
 */

#include <stdio.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

// 栈最大长度
#define MAXSIZE 10

// 栈存储结构
typedef struct {
    ElemType data[MAXSIZE]; // 数据域
    int top1; // 栈1栈顶指针
    int top2; // 栈2栈顶指针
} ShareStack;

/**
 * 初始化栈
 *
 * @param S 要初始化的栈指针
 */
void InitStack(ShareStack *S)
{
    S->top1 = -1;
    S->top2 = MAXSIZE;
}

/**
 * 元素进栈
 *
 * @param S 栈
 * @param i 要进的栈
 * @param e 要进栈的元素
 * @return 1-成功 0-失败
 */
Status Push(ShareStack *S, int i, ElemType e)
{
    if (S->top1 + 1 == S->top2) {
        printf("Push: stack is full, push fails (top1: %d, top2: %d).\n", S->top1, S->top2);
        return ERROR;
    }

    if (i == 1) {
        ++S->top1;
        S->data[S->top1] = e;
    } else {
        --S->top2;
        S->data[S->top2] = e;
    }

    return OK;
}

/**
 * 元素出栈
 *
 * @param S 栈
 * @param i 要操作的栈
 * @param e 出栈的元素保存到 *e
 * @return 1-成功 0-失败
 */
Status Pop(ShareStack *S, int i, ElemType *e)
{
    if ((i == 1 && S->top1 == -1) || (i == 2 && S->top2 == MAXSIZE)) {
        printf("Pop: stack is empty, pop fails.\n");
        return ERROR;
    }

    if (i == 1) {
        *e = S->data[S->top1];
        --S->top1;
    } else {
        *e = S->data[S->top2];
        ++S->top2;
    }

    return OK;
}

/**
 * 打印 S 的内容
 *
 * @param S
 */
void dump(ShareStack S)
{
    if (S.top1 == -1 && S.top2 == MAXSIZE) {
        printf("(dump: stack is empty.)\n");
        return;
    }

    printf("stack 1(top1: %d):\n", S.top1);
    for (int i = 0; i <= S.top1; ++i) {
        printf("%d ", S.data[i]);
    }
    printf("\n");

    printf("stack 2(top2: %d):\n", S.top2);
    for (int i = MAXSIZE - 1; i >= S.top2 && S.top2 < MAXSIZE; --i) {
        printf("%d ", S.data[i]);
    }
    printf("\n");
}

int main()
{
    // 初始化栈
    ShareStack S;
    InitStack(&S);
    dump(S);

    // 进栈1
    Push(&S, 1, 4);
    Push(&S, 1, 5);
    Push(&S, 1, 2);
    dump(S);

    // 出栈1
    ElemType e;
    Pop(&S, 1, &e);
    printf("Pop from stack: %d\n", e);
    dump(S);

    // 进栈2
    Push(&S, 2, 7);
    Push(&S, 2, 56);
    dump(S);

    // 出栈2
    Push(&S, 2, 5);
    Push(&S, 2, 78);
    Push(&S, 2, 123);
    Push(&S, 2, 88);
    Push(&S, 2, 92);
    Push(&S, 2, 192);
    Push(&S, 2, 19209); // full
    dump(S);

    Pop(&S, 2, &e);
    printf("Pop from stack 2: %d\n", e);
    dump(S);

    return 0;
}

/*
(dump: stack is empty.)
stack 1(top1: 2):
4 5 2
stack 2(top2: 10):

Pop from stack: 2
stack 1(top1: 1):
4 5
stack 2(top2: 10):

stack 1(top1: 1):
4 5
stack 2(top2: 8):
7 56
Push: stack is full, push fails (top1: 1, top2: 2).
stack 1(top1: 1):
4 5
stack 2(top2: 2):
7 56 5 78 123 88 92 192
Pop from stack 2: 192
stack 1(top1: 1):
4 5
stack 2(top2: 3):
7 56 5 78 123 88 92
 */
