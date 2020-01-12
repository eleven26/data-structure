//
// Created by ruby on 2020/1/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define OK 1
#define ERROR 0

typedef int Status;

// 线性表的单链表存储结构

typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node* next;
} Node;

typedef struct Node* LinkList; // 定义 LinkList

/**
 * 从链表 L 中读取第 i 个元素，保存其值到 *e
 *
 * 1、跳过链表头节点开始迭代，直到第 i 个元素
 * 2、获取第 i 个元素上保存的 data
 *
 * @param L 线性表
 * @param i 需要读取第 i 个元素
 * @param e 用 e 保存第 i 个元素
 * @return 是否存在，存在返回 1，不存在返回 0
 */
//
Status GetElem(LinkList L, int i, ElemType *e)
{
    // 跳过头节点，从第一个元素开始迭代
    int cursorIndex = 0;
    Node* cursor = L->next;

    // 游标没有到达结尾并且还没到达 i 位置
    while (cursor && cursorIndex < i) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 游标到达了结尾，或者传入的索引不存在
    if (!cursor || cursorIndex > i)
        return ERROR;

    // 取第 i 个元素的数据
    *e = cursor->data;

    return OK;
}

/**
 * 单链表插入。插入元素 e 到链表 L 的第 i 个位置。
 *
 * 1、从头节点开始迭代，直到第 i - 1 个元素
 * 2、为新节点分配内存，将 e 存入新节点的 data 域
 * 3、将新节点和第 i - 1 个节点和第 i 个节点连接起来（指针域更改）
 *
 * @param L 要插入的链表
 * @param i 要插入的位置
 * @param e 要插入的数据
 * @return 1 成功，0 失败
 */
Status ListInsert(LinkList* L, int i, ElemType e)
{
    int cursorIndex = -1;
    LinkList cursor = *L;
    int listEmpty = cursor->next == NULL;

    // 游标移动
    while (cursor->next && cursorIndex < i - 1) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 原链表不存在位置为 i 的元素
    if (listEmpty) {
        // 空链表
        printf("ListInsert: List empty, insert %d to L[0].\n", e);
    } else if (!(cursor->next) || cursorIndex > i - 1) {
        printf("ListInsert: Insert %d to L[%d] fails.\n", e, i);
        return ERROR;
    }

    // 新建需要插入的节点
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = e;
    node->next = cursor->next;

    // node 替代原来链表的第 i 个元素
    cursor->next = node;

    return OK;
}

/**
 * 单链表删除节点。从单链表 L 中删除第 i 个位置的元素，保存其 data 域的值到 *e
 *
 * 1、从 L 的头节点开始迭代，直到第 i - 1 个元素 cursor
 * 2、取得第 i 个元素 cursor->next
 * 3、链接第 i - 1 个元素和第 i + 1 个元素（变更指针域）
 * 4、释放节点 cursor->next
 *
 * @param L 要操作的链表
 * @param i 要删除的位置
 * @param e 删除的元素值
 * @return 1-成功，0-失败
 */
Status ListDelete(LinkList* L, int i, ElemType *e)
{
    int cursorIndex = -1;
    LinkList cursor = *L;

    // 移动游标直到 i - 1 位置
    while (cursor->next && cursorIndex < i - 1) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 判断是否存在
    if (!(cursor->next) || cursorIndex > i - 1) {
        printf("ListDelete: delete L[%d] fails.\n", i);
        return ERROR;
    }

    // 取得需要删除的节点
    LinkList p = cursor->next;
    cursor->next = p->next;
    *e = p->data;

    // 释放节点
    free(p);

    return OK;
}

/**
 * 创建链表，将新节点插入到链表末尾
 *
 * @param L 需要插入元素的链表
 * @param n 插入元素数量
 */
void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L; // r 为指向尾部的节点

    for (int j = 0; j < n; ++j) {
        p = (Node*)malloc(sizeof(Node)); // 生成新节点
        p->data = rand() % 100 + 1; // 随机生成 100 以内的数字
        r->next = p; // 将表尾终端节点的指针指向新节点
        r = p;  // 将当前的新节点定义为表尾终端节点
    }
    r->next = NULL;
}

/**
 * 销毁链表。
 *
 * 单链表整表删除的算法思路如下：
 * 1、声明一节点 p 和 q
 * 2、将第一个节点赋值给 p
 * 3、循环：
 *      * 将下一节点赋值给 q
 *      * 释放 p
 *      * 将 q 赋值给 p
 *
 * @param L 要销毁的链表
 */
void ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL; // 头节点指针域为空
}

/**
 * 打印链表中的所有元素
 *
 * @param L 链表
 */
Status dump(LinkList L)
{
    LinkList cursor;
    cursor = L->next;

    if (!cursor) {
        printf("L is empty.\n");
        return ERROR;
    }

    while (cursor) {
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }
    printf("\n");

    return OK;
}

int main() {
    LinkList L;
    CreateListTail(&L, 5);
    dump(L);

    // 获取某一个元素
    ElemType e;
    GetElem(L, 3, &e);
    printf("L[3]=%d.\n", e);

    // 测试插入到第 0 个元素
    printf("insert 1 to L[0].\n");
    ListInsert(&L, 0, 1);
    dump(L);

    // 测试删除第 0 个元素
    printf("delete L[0].\n");
    ListDelete(&L, 0, &e);
    dump(L);

    // 清空
    ClearList(&L);
    dump(L);

    // 测试插入到空链表
    printf("insert 3 to Empty L.\n");
    ListInsert(&L, 0, 3);
    dump(L);

    // 删除只有一个元素的链表
    printf("delete only element from L.\n");
    ListDelete(&L, 0, &e);
    printf("deleted e: %d\n", e);
    dump(L);
}
