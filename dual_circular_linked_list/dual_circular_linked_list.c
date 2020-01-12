//
// Created by ruby on 2020/1/12.
//

/**
 * 双向循环链表
 *
 * 和普通的双向链表的差别在于判断结尾节点的方法 isTail。
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

// 线性表的单链表存储结构

typedef int ElemType;

typedef struct Node
{
    struct Node* prior;
    ElemType data;
    struct Node* next;
} Node;

typedef struct Node* DualLinkList; // 定义 LinkList

/**
 * 是否 node 是尾节点（判断方式：node->next 是否指向链表头节点）
 *
 * @param L
 * @param node
 * @return
 */
Status isTail(DualLinkList L, Node* node)
{
    if (L == node->next)
        return TRUE;

    return FALSE;
}

/**
 * 从双向链表 L 中获取第 i 个元素，保存到 *e 中
 *
 * 1、跳过头节点开始循环直到第 i 个元素
 * 2、获取第 i 个元素的 data 域，保存到 *e
 *
 * @param L 线性表
 * @param i 需要读取第 i 个元素
 * @param e 用 e 保存第 i 个元素
 * @return 是否存在，存在返回 1，不存在返回 0
 */
Status GetElem(DualLinkList L, int i, ElemType *e)
{
    int cursorIndex = 0; //
    DualLinkList cursor = L->next; // 游标

    // 循环 i 次
    while (!isTail(L, cursor) && cursorIndex < i) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    if (isTail(L, cursor) || cursorIndex > i) {
        printf("L[%d] not in L.\n", i);
        return ERROR;
    }

    // 第 i 个位置上的元素
    *e = cursor->data;

    return OK;
}

/**
 * 插入 e 到双向链表 L 的第 i 个位置
 *
 * 1、从头节点开始遍历，直到第 i - 1 个位置 p
 * 2、新建节点，保存 e 到其 data 域
 * 3、链接 i - 1 和 新节点 和 i
 *
 * @param L 要插入的链表
 * @param i 要插入的位置
 * @param e 要插入的数据
 * @return 1 成功，0 失败
 */
Status ListInsert(DualLinkList *L, int i, ElemType e)
{
    int cursorIndex = -1;
    DualLinkList cursor = *L;
    int listEmpty = cursor->next == NULL;

    // 循环直到 i - 1
    while (!isTail(*L, cursor) && cursorIndex < i - 1) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    if (listEmpty && i == 0) {
        // 双向链表为空
        printf("ListInsert: L is empty, insert %d to L[0].\n", e);
    } else if (isTail(*L, cursor) || cursorIndex > i - 1) {
        // i 超出了范围
        printf("%d is out of range.\n", i);
        return ERROR;
    }

    // 新建节点
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;

    if (listEmpty) {
        // 双向链表为空的时候，只需要添加一个节点到末尾就可以
        // 三个指针域变更

        node->next = NULL;
        node->prior = cursor;
    } else {
        // 四个指针域的变更

        // 链接新节点和旧的 i
        node->next = cursor->next;
        // 链接 node 到旧的 i 的 prior
        cursor->next->prior = node;
        // 链接 node 的 prior 到 cursor
        node->prior = cursor;
    }

    // 链接 cursor->next 到 node
    cursor->next = node;

    return OK;
}

/**
 * 双向链表删除节点
 *
 * 1、从头节点开始遍历，直到第 i - 1 个元素
 * 2、记录待删除的节点
 * 3、更改前后指针的指针域
 *
 * @param L 要操作的链表
 * @param i 要删除的位置
 * @param e 删除的元素值
 * @return 1-成功，0-失败
 */
Status ListDelete(DualLinkList * L, int i, ElemType *e)
{
    int cursorIndex = -1;
    DualLinkList cursor = *L;

    // 遍历直至 i - 1
    while (!isTail(*L, cursor) && cursorIndex < i - 1) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 下标超出范围
    if (isTail(*L, cursor) || cursorIndex > i - 1) {
        printf("%d out of range.\n", i);
        return ERROR;
    }

    // 待删除的节点
    DualLinkList p = cursor->next;

    // 记录要被删除的元素
    *e = p->data;

    if (cursor->next->next) {
        // 不是最后一个节点
        cursor->next->next->prior = cursor;
        cursor->next = cursor->next->next;
    } else {
        cursor->next = NULL;
    }

    // 释放节点
    free(p);

    return OK;
}

/**
 * 创建双向链表，将新节点插入到链表末尾
 *
 * 1、初始化头节点，游标指向头节点
 * 2、新建需要插入的节点，让其 prior 指针指向当前游标，让其 后继 指针指向 NULL
 * 3、修改 cursor 的后继节点为上一步新建的新节点
 * 4、移动游标
 *
 * @param L 需要插入元素的链表
 * @param n 插入元素数量
 */
void CreateListTail(DualLinkList *L, int n)
{
    srand(time(0));

    // 初始化头节点
    *L = (DualLinkList)malloc(sizeof(Node));

    DualLinkList cursor = *L; // 游标
    Node* node; // 保存最新创建的节点

    for (int i = 0; i < n; ++i) {
        // 创建新节点
        node = (Node*)malloc(sizeof(Node));
        node->prior = cursor;
        node->data = rand() % 100 + 1;
        node->next = NULL;
        
        // 将新节点链接到链表末尾
        cursor->next = node;

        // 移动游标
        cursor = node;
    }
}

/**
 * 销毁双向链表。只保留一个头节点。
 *
 * 双向链表整表删除的算法思路如下：
 * 1、定义一个游标，指向双向链表的头节点
 * 2、循环双向链表，直到 cursor->next 为 NULL（最后的一个节点）
 *
 * @param L 要销毁的双向链表
 */
void ClearList(DualLinkList *L)
{
    Node* node = *L; // 游标
    Node* p; // 待删除的节点

    while (node->next) {
        p = node->next;

        // 1. node->next 还有后继节点
        // 2. node->next 没有后继节点了
        if (node->next->next) {
            node->next = node->next->next;
            node->next->prior = node;
        } else {
            node->next = NULL;
        }

        // 释放要删除的节点
        free(p);
    }
}

/**
 * 打印双向链表中的所有元素（和单向链表一致）
 *
 * @param L 链表
 */
void dump(DualLinkList L)
{
    DualLinkList cursor = L->next; // 游标

    if (!cursor) {
        printf("(List is empty.)\n");
        return;
    }

    while (cursor) {
        if (cursor == L->next)
            printf("%d(prior: NULL) ", cursor->data);
        else
            printf("%d(prior: %d) ", cursor->data, cursor->prior->data);
        cursor = cursor->next;
    }
    printf("\n");
}

int main() {
    DualLinkList L;
    CreateListTail(&L, 5);
    dump(L);

    // 获取某一个元素
    ElemType e;
    GetElem(L, 2, &e);
    printf("L[2]=%d\n", e);

    // 插入元素
    printf("insert 40 to L[2].\n");
    ListInsert(&L, 2, 40);
    dump(L);

    // 测试插入到第一个位置
    ElemType r = rand() % 100 + 1;
    printf("insert %d into L[0].\n", r);
    ListInsert(&L, 0, r);
    dump(L);

    // 测试删除第一个位置
    printf("deleting the first element.\n");
    ListDelete(&L, 0, &e);
    printf("deleted: %d\n", e);
    dump(L);

    // 测试删除最后一个位置
    printf("deleting the last element.\n");
    ListDelete(&L, 5, &e);
    printf("deleted: %d\n", e);
    dump(L);

    // 清空
    ClearList(&L);
    dump(L);
}
