//
// Created by ruby on 2020/1/12.
//

// 循环链表
// 将单链表中终端节点的指针域由空指针改为指向头节点，就使整个单链表形成一个环，
// 这种头尾相接的单链表称为单循环链表，简称循环链表（circular linked list）

// 循环链表解决了一个很麻烦的问题。如何从当中一个节点出发，访问到链表的全部节点。

// 为了使空链表与非空链表处理一致，我们通常设一个头节点。

/**
 * 循环链表和单链表的主要差异就在于循环的判断条件上，原来是判断 p->next 是否为空，现在则是 p->next 不等于头节点，则循环未结束。
 *
 * 在单链表中，我们有了头节点时，我们可以用 O(1) 的时间访问第一个节点，但对于要访问到最后一个节点，却需要 O(n) 时间，
 * 因为我们需要将单链表全部扫描一遍。
 *
 * 有没有可能用 O(1) 时间由链表指针访问到最后一个节点呢？当然可以。
 * 不过我们需要改造一下这个循环链表，不用头指针，而是用指向终端节点的尾指针来表示循环链表，此时查找开始节点和终端节点都很方便了。
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
    ElemType data;
    struct Node* next;
} Node;

typedef struct Node* LinkList; // 定义 LinkList

/**
 * node 是否是尾节点（判断方式：node->next 是否指向链表头节点）
 *
 * @param L
 * @param node
 * @return
 */
Status isTail(LinkList L, Node* node)
{
    if (L == node)
        return TRUE;

    return FALSE;
}

/**
 * 循环链表的读取：获取循环链表 L 中的第 i 个元素，保存到 *e。
 *
 * 1、从第一个元素开始逐个读取链表数据，直到第 i 个元素
 * 2、获取第 i 个元素里的数据，保存到 *e
 *
 * @param L 线性表
 * @param i 需要读取第 i 个元素
 * @param e 用 e 保存第 i 个元素
 * @return 是否存在，存在返回 1，不存在返回 0
 */
Status GetElem(LinkList L, int i, ElemType *e)
{
    int cursorIndex = 0; // 游标所在索引
    LinkList cursor = L->next;   // 游标

    // cursor 移动到 i 位置
    while (!isTail(L, cursor) && cursorIndex < i) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 游标到达了结尾，或者传入的索引不存在
    if (isTail(L, cursor) || cursorIndex > i) {
        printf("GetElem fails: unable to locate L[i].\n");
        return ERROR;
    }

    // 取第 i 个元素的数据
    *e = cursor->data;

    return OK;
}

/**
 * 循环链表的插入。插入元素 e 到循环链表 L 的第 i 个位置。
 *
 * 1、从链表第一个元素开始迭代（头节点直接跳过）
 * 2、找到第 i - 1 个元素，因为插入元素要和前一个元素（第 i - 1 个元素）连接起来
 * 3、新建要插入的节点，初始化该节点
 * 4、把该节点插入第 i - 1 和第 i 个元素之间
 *
 * @param L 要插入的链表
 * @param i 要插入的位置
 * @param e 要插入的数据
 * @return 1 成功，0 失败
 */
Status ListInsert(LinkList* L, int i, ElemType e)
{
    // 为了可以插入到下标 0 的位置，所以需要从头节点开始迭代，区别于其它一些从第一个元素开始迭代的方法
    int cursorIndex = -1;
    LinkList cursor = *L;       // 游标指向头节点

    // 游标移动
    while (!isTail(*L, cursor->next) && cursorIndex < i - 1) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 原链表不存在位置为 i 的元素
    if (isTail(*L, cursor->next) || cursorIndex > i - 1) {
        printf("insert %d into L[%d] fails. \n", e, i);
        return ERROR;
    }

    // 新建需要插入的节点
    Node* s = (Node*)malloc(sizeof(Node));
    s->data = e;
    s->next = cursor->next;

    // node 替代原来链表的第 i 个元素
    cursor->next = s;

    return OK;
}

/**
 * 循环链表删除节点。删除循环链表 L 中第 i 个元素，里面的值使用 *e 保存。
 *
 * 1、从头节点开始遍历，直到第 i - 1 个节点为止（因为要把第 i - 1 这个节点和第 i + 1 个节点连接起来，释放第 i 个节点）
 * 2、定义临时节点 p 保存第 i 个节点
 * 3、第 i - 1 个节点的尾指针指向 p->next
 * 4、*e 保存第 i 个节点的值：*e = p->data;
 * 5、释放第 i 个节点：free(p)
 *
 * @param L 要操作的链表
 * @param i 要删除的位置
 * @param e 删除的元素值
 * @return 1-成功，0-失败
 */
Status ListDelete(LinkList* L, int i, ElemType *e)
{
    int cursorIndex = -1;        // 游标位置
    LinkList cursor = *L; // 游标

    // 移动游标直到 i - 1 位置
    while (!isTail(*L, cursor->next) && cursorIndex < i - 1) {
        cursor = cursor->next;
        ++cursorIndex;
    }

    // 判断是否存在
    if (isTail(*L, cursor->next) || cursorIndex > i - 1) {
        printf("Unable to locate L[%d].\n", i);
        return ERROR;
    }

    // 取得需要删除的节点
    Node* node = cursor->next;
    cursor->next = node->next;
    *e = node->data;

    // 释放节点
    free(node);

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
    r->next = *L;
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
    while (!isTail(*L, p)) {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = *L; // 头节点指针域为空
}

/**
 * 打印链表中的所有元素
 *
 * @param L 链表
 */
int dump(LinkList L)
{
    LinkList cursor;
    cursor = L->next;

    if (isTail(L, cursor)) {
        printf("(L is empty.)");
        return ERROR;
    }

    while (!isTail(L, cursor)) {
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }
    printf("\n");

    return OK;
}

int main() {
    // 初始化链表
    LinkList L;
    CreateListTail(&L, 5);
    dump(L);

    // 获取某一个元素
    ElemType e;
    GetElem(L, 3, &e);
    printf("L[3]=%d\n", e);

    // 插入元素
    printf("insert 40 to L[2]\n");
    ListInsert(&L, 2, 40);
    dump(L);

    // 删除元素
    ListDelete(&L, 3, &e);
    printf("delete L[3] from L: %d.\n", e);
    dump(L);

    // 插入元素到第一位
    printf("insert 3 to L[0].\n");
    ListInsert(&L, 0, 3);
    dump(L);

    // 删除第一位的元素
    ListDelete(&L, 0, &e);
    printf("delete L[0] from L: %d.\n", e);
    dump(L);

    // 清空
    printf("clear L.\n");
    ClearList(&L);
    dump(L);
}
