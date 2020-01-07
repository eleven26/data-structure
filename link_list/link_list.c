//
// Created by ruby on 2020/1/7.
//

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
    ElemType data;
    struct Node* next;
} Node;

typedef struct Node* LinkList; // 定义 LinkList

/**
 * 单链表的读取
 * 在单链表中，由于第 i 个元素到底在哪？没有办法一开始就知道，必须得从头开始找。
 * 因此，对于单链表实现获取第 i 个元素的数据的操作 GetElem，在算法上，相对要麻烦一些。
 *
 * 获取链表第 i 个数据的算法思路：
 * 1、声明一个节点 p 指向链表第一个节点，初始化 j 从 1 开始
 * 2、当 j < 1 时，就遍历链表，让 p 的指针向后移动，不断指向下一节点，j 累加 1
 * 3、若到链表末尾 p 为空，则说明第 i 个元素不存在
 * 4、若查找成功，返回节点 p 的数据
 *
 * @param L 线性表
 * @param i 需要读取第 i 个元素
 * @param e 用 e 保存第 i 个元素
 * @return 是否存在，存在返回 1，不存在返回 0
 */
//
Status GetElem(LinkList L, int i, ElemType *e)
{
    // 当前游标位置
    int index;
    // 游标
    LinkList cursor;
    cursor = L->next; // 让游标指向第一个节点
    index = 1;  // 游标所在索引

    // 游标没有到达结尾并且还没到达 i 位置
    while (cursor && index < i) {
        cursor = cursor->next;
        ++index;
    }
    // 游标到达了结尾，或者传入的索引不存在
    if (!cursor || index > i)
        return ERROR;

    // 取第 i 个元素的数据
    *e = cursor->data;

    return OK;
}

/**
 * 单链表插入。 s->next = p->next; p->next = s;
 *
 * 初始条件：顺序线性表 L 以存在，1 <= i <= ListLength(L)
 * 操作结果：在 L 中第 i 个位置之前插入新的数据元素 e，L 的长度加 1
 *
 * 单链表第 i 个数据插入节点的算法思路:
 * 1、声明一个节点 cursor 指向链表的第一个节点，初始化 index 从 1 开始
 * 2、当 index < i 时，就遍历链表，让 p 的指针向后移动，不断移向下一节点，index 累加 1
 * 3、若到链表末尾 p 为空，则说明第 i 个元素不存在
 * 4、否则查找成功，在系统中生成一个空节点 s
 * 5、将数据元素 e 赋值给 s->data
 * 6、单链表的插入标准语句：s->next = cursor->next; cursor->next = s
 * 7、返回成功
 *
 * @param L 要插入的链表
 * @param i 要插入的位置
 * @param e 要插入的数据
 * @return 1 成功，0 失败
 */
Status ListInsert(LinkList* L, int i, ElemType e)
{
    int index = 1;        // 从第 1 个节点开始算，目的是拿到第 i - 1 个节点
    LinkList cursor = *L; // 游标指向第一个节点

    // 游标移动
    while (cursor && index < i) {
        cursor = cursor->next;
        ++index;
    }

    // 原链表不存在位置为 i 的元素
    if (!cursor || index > i)
        return ERROR;

    // 新建需要插入的节点
    LinkList s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = cursor->next;

    // node 替代原来链表的第 i 个元素
    cursor->next = s;

    return OK;
}

/**
 * 单链表删除节点. p->next = p->next->next;
 *
 * 初始条件：顺序线性表 L 以存在， 1 <= i <= ListLength(L)
 * 操作结果：删除 L 的第 i 个数据元素，并用 e 返回其值，L 的长度减 1
 *
 * 单链表第 i 个数据删除节点的算法思路:
 * 1、声明一节点 cursor 指向链表第一个节点，初始化 index 从 1开始
 * 2、当 index < i 时，就遍历链表，让 cursor 指针向后移动，不断指向下一个节点，index 累加 1
 * 3、若到链表结尾 cursor 为空，则说明第 i 个元素不存在
 * 4、否则查找成功，将欲删除的节点 cursor->next 赋值给 q
 * 5、单链表的删除标准语句 cursor->next = q->next
 * 6、将 q 节点中的数据赋值给 e，作为返回
 * 7、释放 q 节点
 * 8、返回成功
 *
 * @param L 要操作的链表
 * @param i 要删除的位置
 * @param e 删除的元素值
 * @return 1-成功，0-失败
 */
Status ListDelete(LinkList* L, int i, ElemType *e)
{
    int index = 1;        // 游标位置（从 1 开始的目的：cursor 最终到达的是目标节点 i 的前一个节点）
    LinkList cursor = *L; // 游标

    // 移动游标直到 i - 1 位置
    while (cursor->next && index < i) {
        cursor = cursor->next;
        ++index;
    }

    // 判断是否存在
    if (!(cursor->next) || index > i)
        return ERROR;

    // 取得需要删除的节点
    LinkList p = cursor->next;
    cursor->next = p->next;
    *e = p->data;

    // 释放节点
    free(p);

    return OK;
}

/**
 * 创建单链表。
 *
 * 随机生成 n 个元素的值，建立带表头节点的单链线性表（头插表）
 *
 * 单链表整表创建的算法思路：
 * 1、声明一节点 p 和计数器变量 i
 * 2、初始化一空链表 L
 * 3、让 L 的头节点的指针指向 NULL，即建立一个带头节点的单链表
 * 4、循环：
 *      * 生成一新节点赋值给 p
 *      * 随机生成一数字赋值给 p 的数据域 p->data
 *      * 将 p 插入到头节点与前一新节点之间
 *
 * @param L
 * @param n
 */
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0)); // 初始化随机数种子
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL; // 建立一个带头节点的单链表

    for (int j = 0; j < n; ++j) {
        p = (LinkList)malloc(sizeof(Node)); // 生成新节点
        p->data = rand() % 100 + 1; // 随机生成 100 以内的数字
        p->next = (*L)->next;
        (*L)->next = p; // 插入到表头
    }
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
    int i;
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
void dump(LinkList L)
{
    LinkList cursor;
    cursor = L->next;
    while (cursor) {
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }
    printf("\n");
}

int main() {
    LinkList L;
    CreateListTail(&L, 5);
    dump(L);

    // 获取某一个元素
    ElemType e;
    GetElem(L, 3, &e);
    printf("L[3]=%d\n", e);

    // 清空
    ClearList(&L);
    dump(L);
}
