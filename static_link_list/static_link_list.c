//
// Created by ruby on 2020/1/7.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef int ElemType;

#define MAXSIZE 1000

typedef struct {
    ElemType data;
    int cur; // 游标，为 0 时表示无指向
} StaticLinkList[MAXSIZE];

/**
 * 将一维数组 space 中各分量链成一备用链表
 * space[0].cur 为头指针，"0" 表示空指针
 *
 * @param space
 * @return
 */
Status InitList(StaticLinkList space)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; ++i)
        space[i].cur = i + 1;
    space[MAXSIZE].cur = 0;
    return OK;
}

/**
 * 若备用空间链表非空，则返回分配的节点下标，否则返回 0
 *
 * @param space
 * @return
 */
int MallocSLL(StaticLinkList space)
{
    // 当前数组第一个元素的 cur 存的值，就是要返回的第一个备用空闲的下标
    int i = space[0].cur;
    if (space[0].cur)
        space[0].cur = space[i].cur; // 由于要拿出一个分量来使用了，所以我们就得把它的下一个分量用来做备用
    return i;
}

/**
 * 返回 L 中数据元素的个数
 *
 * @param L
 * @return
 */
int ListLength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;
    while (i) {
        i = L[i].cur;
        j++;
    }
    return j;
}

/**
 * 在 L 中第 i 个元素之前插入新的数据元素 e
 *
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j, k, l;
    k = MAXSIZE - 1; // 注意 k 首先是最后一个元素的下标
    if (i < 1 || i > ListLength(L) + 1)
        return ERROR;
    j = MallocSLL(L); // 获得空闲分量的下标
    if (j) {
        L[j].data = e; // 将数据赋值给此分量的 data
        for (l = 1; l < i - 1; l++) { // 找到第 i 个元素之前的位置
            k = L[k].cur;
        }
        L[j].cur = L[k].cur; // 把第 i 个元素之前的 cur 赋值给新元素的 cur
        L[k].cur = j; // 把新元素的下标赋值给第 i 个元素之前元素的 cur
        return OK;
    }
    return ERROR;
}

/**
 * 将下标为 k 的空闲节点回收到备用链表
 *
 * @param space
 * @param k
 */
void FreeSLL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

/**
 * 删除在 L 中第 i 个数据元素 e
 *
 * @param L
 * @param i
 * @return
 */
Status ListDelete(StaticLinkList L, int i)
{
    int j, k;
    if (i < 1 || i > ListLength(L))
        return ERROR;
    k = MAXSIZE - 1;
    for (j = 0; j <= i - 1; ++j) // 找到第 i 个元素之前的位置
        k = L[k].cur;
    j = L[k].cur;
    L[k].cur = L[j].cur;
    FreeSLL(L, j);
    return OK;
}

/**
 * 打印静态链表
 *
 * @param L
 */
void dump(StaticLinkList L)
{
    // 长度
    printf("length: %d\n", ListLength(L));

    // 数据域
    printf("data: \n");
    int i = L[MAXSIZE - 1].cur;
    while (i) {
        printf("%d => %d, ", i, L[i].data);
        i = L[i].cur;
    }
}

int main()
{
    StaticLinkList L;
    InitList(L);

    ListInsert(L, 1, 12);
    ListInsert(L, 1, 14);
    dump(L);

    ListDelete(L, 1);
    dump(L);
}
