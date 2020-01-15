//
// Created by ruby on 2020/1/14.
//

/**
 * 链栈
 */

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node *next;
} Node;

// 链栈存储结构
typedef struct {
    Node *top;
    int length;
} LinkStack;

/**
 * 初始化栈
 *
 * @param S 要初始化的栈指针
 */
void InitStack(LinkStack *S)
{
    S->top = NULL;
    S->length = 0;
}

/**
 * 元素进栈
 *
 * @param S 栈
 * @param e 要进栈的元素
 * @return 1-成功 0-失败
 */
Status Push(LinkStack *S, ElemType e)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;
    node->next = S->top;

    S->top = node;
    ++S->length;

    return OK;
}

/**
 * 元素出栈
 *
 * @param S 栈
 * @param e 出栈的元素保存到 *e
 * @return 1-成功 0-失败
 */
Status Pop(LinkStack *S, ElemType *e)
{
    if (S->length == 0) {
        printf("Pop fails: stack is empty.\n");
        return ERROR;
    }

    Node *p = S->top;
    // 栈顶指针指向下一个
    S->top = p->next;
    // 保存栈顶元素
    *e = p->data;
    // 栈长度减1
    --S->length;
    free(p);

    return OK;
}

/**
 * 打印 S 的内容
 *
 * @param S
 */
void dump(LinkStack S)
{
    if (S.length == 0) {
        printf("(dump: S is empty.)\n");
        return;
    }

    printf("Stack length: %d.\n", S.length);
    printf("Top to end: ");

    Node *cursor = S.top;
    while (cursor) {
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }

    printf("\n");
}

int main()
{
    LinkStack LS;
    InitStack(&LS);

    // 进栈测试
    Push(&LS, 5);
    Push(&LS, 17);
    Push(&LS, 1);
    dump(LS);

    // 出栈测试
    ElemType e;
    Pop(&LS, &e);
    printf("Pop %d from S.\n", e);
    dump(LS);

    return 0;
}
