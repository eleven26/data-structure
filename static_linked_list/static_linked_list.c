//
// Created by ruby on 2020/1/12.
//

/**
 * 静态链表
 *
 * 初始化使用 L[0] 存储空闲静态链表的头节点的下标。
 * 初始化使用 L[MAXSIZE - 1] 存储链表头节点的下标。
 */

#include <stdio.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

// 静态链表最大长度
#define MAXSIZE 5

// 静态链表存储结构
typedef struct {
    ElemType data; // 数据域
    int next; // 游标
} Node;

typedef Node StaticLinkedList[MAXSIZE];

/**
 * 初始化静态链表
 *
 * @param L 需要初始化的静态链表
 */
void InitStaticLinkedList(StaticLinkedList L)
{
    // 空静态链表初始化，每一个元素的 next 域指向后一个元素
    for (int i = 0; i < MAXSIZE - 1; ++i) {
        if (i == MAXSIZE - 2) // 初始化的时候倒数第二个元素没有后继的空闲节点了
            L[i].next = 0;
        else
            L[i].next = i + 1;
    }

    // 非空闲静态链表的起始节点下标为 0，意味着为空
    L[MAXSIZE - 1].next = 0;
    L[MAXSIZE - 1].data = 0;
}

/**
 * 获取空闲的节点下标
 *
 * @param L 从静态链表 L 中获取下一个空闲的节点下标
 * @return 下一个空闲节点的下标
 */
int GetIdleIndex(StaticLinkedList L)
{
    int idleIndex = L[0].next;

    if (idleIndex == 0) {
        // 1. 已满
        return 0;
    } else {
        // 2. 未满
        L[0].next = L[idleIndex].next;
        return idleIndex;
    }
}

/**
 * 释放静态链表的第 i 个节点（释放的节点插入到空闲链表的头部）
 *
 * @param L 要操作的静态链表
 * @param i 节点所在索引
 */
void FreeNode(StaticLinkedList L, int i)
{
    i++; // i + 1 才是在 L 中的下标
    L[i].next = L[0].next;
    L[i].data = 0;
    L[0].next = i;
}

/**
 * 获取静态链表第 i 个元素，保存其 data 域的值到 *e
 *
 * @param L 静态链表
 * @param i 第 i 个元素
 * @param e 保存第 i 个元素
 * @return 1-成功 0-失败
 */
Status GetElem(StaticLinkedList L, int i, ElemType *e)
{
    int cursorIndex = -1;
    Node cursor = L[MAXSIZE - 1];

    // 移动到 i 位置
    while (cursor.next && cursorIndex < i) {
        cursor = L[cursor.next];
        ++cursorIndex;
    }

    if (!cursor.next && cursorIndex == i) {
        // 非空链表最后一个元素
    } else if (!cursor.next || cursorIndex > i) {
        // 不存在 i
        printf("Unable to locate L[%d].\n", i);
        return ERROR;
    }

    *e = cursor.data;

    return OK;
}

/**
 * 将 e 插入到静态链表 L 的第 i 个位置
 *
 * @param L 要操作的静态链表
 * @param i 要插入的位置
 * @param e 要插入的数据
 * @return 1-成功 0-失败
 */
Status ListInsert(StaticLinkedList L, int i, ElemType e)
{
    int cursorIndex = -1;
    Node cursor = L[MAXSIZE - 1]; // 非空闲链表头节点
    int listEmpty = L[MAXSIZE - 1].next == 0;

    // 移动到第 i - 1 个位置
    while (cursor.next && cursorIndex < i - 1) {
        cursor = L[cursor.next];
        ++cursorIndex;
    }

    if (i == 0) {
        printf("ListInsert: List is empty.\n");
    } else if (!cursor.next || cursorIndex > i - 1) {
        // 不存在 i
        printf("ListInsert: Unable to locate L[%d]\n", i);
        return ERROR;
    }

    // 获取空闲节点下标
    int idleIndex = GetIdleIndex(L);
    if (!idleIndex) {
        printf("ListInsert: L is full. Unable to insert any more element.\n");
        return ERROR;
    }

    // 保存数据域
    L[idleIndex].data = e;

    // 1. 新节点指针域修改
    // 2. i - 1 的 next 域指向 idleIndex
    if (listEmpty) {
        L[idleIndex].next = 0;
        L[MAXSIZE - 1].next = idleIndex;
    } else {
        L[idleIndex].next = L[cursor.next].next;
        L[cursor.next].next = idleIndex;
    }

    return OK;
}

/**
 * 从静态链表 L 中删除第 i 个元素，保存其 data 域到 *e
 *
 * @param L 要操作的静态链表
 * @param i 要删除的位置
 * @param e 保存被删除元素的 data 域
 * @return 1-成功 0-失败
 */
Status ListDelete(StaticLinkedList L, int i, ElemType *e)
{
    int cursorIndex = -1;
    Node cursor = L[MAXSIZE - 1]; // 非空闲链表头节点
    int listEmpty = L[MAXSIZE - 1].next == 0;
    int current = MAXSIZE - 1;

    if (listEmpty) {
        printf("ListDelete: list empty, delete fails.\n");
        return ERROR;
    }

    // cursor.next 是每一个元素的 next 域，指示着下一个元素的下标，如果为 0 说明到达了末尾。

    // 移动到第 i - 1 个元素处
    while (cursor.next && cursorIndex < i - 1) {
        current = cursor.next;
        cursor = L[cursor.next];
        ++cursorIndex;
    }

    if (!cursor.next || cursorIndex > i - 1) {
        printf("ListDelete: Unable to locate L[%i]\n", i);
    }

    // L[cursor.next] 是第 i 个元素，是即将被删除的元素
    *e = L[cursor.next].data;

    // 非空闲链表移除元素（节点变动）
    if (cursorIndex == -1) {
        L[MAXSIZE - 1].next = L[cursor.next].next;
    } else {
        L[cursor.next].next = L[current].next;
    }

    FreeNode(L, i);

    return OK;
}

/**
 * 打印静态链表
 *
 * @param L
 */
void dump(StaticLinkedList L)
{
    printf("\n-------------\n");

    for (int i = 0; i < MAXSIZE; ++i) {
        printf("| %d | %d | %d |\n", i, L[i].data, L[i].next);
    }

    printf("-------------\n\n");
}

int main()
{
    StaticLinkedList L;
    InitStaticLinkedList(L);
    dump(L);

    // 插入元素测试
    ListInsert(L, 0, 3);
    dump(L);

    ListInsert(L, 0, 5);
    dump(L);

    ListInsert(L, 1, 7);
    dump(L);

    // 获取元素测试
    ElemType e;
    GetElem(L, 0, &e);
    printf("L[0] = %d\n", e);
    GetElem(L, 1, &e);
    printf("L[1] = %d\n", e);
    GetElem(L, 2, &e);
    printf("L[2] = %d\n", e);

    // 删除元素测试
    ListDelete(L, 1, &e);
    dump(L);
    printf("deleted %d\n", e);

    ListDelete(L, 0, &e);
    dump(L);
    printf("deleted %d\n", e);

    ListDelete(L, 0, &e);
    dump(L);
    printf("deleted %d\n", e);

    return 0;
}

/*
-------------
| 0 | 0 | 1 |
| 1 | 0 | 2 |
| 2 | 0 | 3 |
| 3 | 0 | 0 |
| 4 | 0 | 0 |
-------------

ListInsert: List is empty.

-------------
| 0 | 0 | 2 |
| 1 | 3 | 0 |
| 2 | 0 | 3 |
| 3 | 0 | 0 |
| 4 | 0 | 1 |
-------------

ListInsert: List is empty.

-------------
| 0 | 0 | 3 |
| 1 | 3 | 2 |
| 2 | 5 | 0 |
| 3 | 0 | 0 |
| 4 | 0 | 1 |
-------------


-------------
| 0 | 0 | 0 |
| 1 | 3 | 2 |
| 2 | 5 | 3 |
| 3 | 7 | 0 |
| 4 | 0 | 1 |
-------------

L[0] = 3
L[1] = 5
L[2] = 7

-------------
| 0 | 0 | 2 |
| 1 | 3 | 3 |
| 2 | 0 | 0 |
| 3 | 7 | 0 |
| 4 | 0 | 1 |
-------------

deleted 5

-------------
| 0 | 0 | 1 |
| 1 | 0 | 2 |
| 2 | 0 | 0 |
| 3 | 7 | 0 |
| 4 | 0 | 3 |
-------------

deleted 3

-------------
| 0 | 0 | 1 |
| 1 | 0 | 1 |
| 2 | 0 | 0 |
| 3 | 7 | 0 |
| 4 | 0 | 0 |
-------------

deleted 7
 */
