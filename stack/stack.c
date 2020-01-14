//
// Created by ruby on 2020/1/14.
//

/**
 * 栈
 */

#include <stdio.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

// 栈最大长度
#define MAXSIZE 5

// 栈存储结构
typedef struct {
    ElemType data[MAXSIZE]; // 数据域
    int top; // 栈顶指针
} Stack;

/**
 * 初始化栈
 *
 * @param S 要初始化的栈指针
 */
void InitStack(Stack *S)
{
    S->top = -1;
}

/**
 * 元素进栈
 *
 * @param S 栈
 * @param e 要进栈的元素
 * @return 1-成功 0-失败
 */
Status Push(Stack *S, ElemType e)
{
    if (S->top == MAXSIZE - 1) {
        printf("Push: stack is full, push fails.\n");
        return ERROR;
    }

    ++S->top;
    S->data[S->top] = e;

    return OK;
}

/**
 * 元素出栈
 *
 * @param S 栈
 * @param e 出栈的元素保存到 *e
 * @return 1-成功 0-失败
 */
Status Pop(Stack *S, ElemType *e)
{
    if (S->top == -1) {
        printf("Pop: stack is empty, pop fails.\n");
        return ERROR;
    }

    *e = S->data[S->top];
    --S->top;

    return OK;
}

/**
 * 打印 S 的内容
 *
 * @param S
 */
void dump(Stack S)
{
    if (S.top == -1) {
        printf("(dump: stack is empty.)\n");
        return;
    }

    for (int i = 0; i <= S.top; ++i) {
        printf("%d ", S.data[i]);
    }
    printf("\n");
}

int main()
{
    // 初始化栈
    Stack S;
    InitStack(&S);
    dump(S);

    // 进栈
    Push(&S, 4);
    Push(&S, 5);
    Push(&S, 2);
    dump(S);

    // 出栈
    ElemType e;
    Pop(&S, &e);
    printf("Pop from stack: %d\n", e);
    dump(S);
    Pop(&S, &e);
    Pop(&S, &e);
    dump(S);

    return 0;
}

/*
(dump: stack is empty.)
4 5 2
Pop from stack: 2
4 5
(dump: stack is empty.)
 */