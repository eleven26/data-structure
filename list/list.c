//
// Created by ruby on 2020/1/13.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

// 线性表最大长度
#define MAXSIZE 5

typedef struct {
    int length;
    int size;
    ElemType data[MAXSIZE];
} List;

/**
 * 初始化线性表
 *
 * @param L 需要初始化的线性表
 * @return 1-成功 0-失败
 */
Status InitList(List *L)
{
    for (int i = 0; i < MAXSIZE; ++i) {
        (*L).data[i] = 0;
    }

    (*L).length = 0;
    (*L).size = MAXSIZE;

    return OK;
}

/**
 * 打印线性表
 *
 * @param L
 */
void dump(List L)
{
    if (L.length == 0) {
        printf("(L is empty.)\n");
        return;
    }

    for (int i = 0; i < L.size; ++i) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

/**
 * 插入元素 e 到线性表 L 的第 i 个位置
 *
 * @param L 要插入到的线性表
 * @param i 要插入到的位置
 * @param e 要插入的元素
 * @return 1-成功 0-失败
 */
Status ListInsert(List *L, int i, ElemType e)
{
    // 临界条件判断
    if (i < 0 || i > (*L).length || (*L).length >= (*L).size) {
        printf("ListInsert: index out of range, insert %d fails.\n", e);
        return ERROR;
    }

    (*L).length++;

    // 从 i 开始往后移动
    // 边界：最后一位
    for (int j = (*L).length - 1; j > i; --j) {
        (*L).data[j] = (*L).data[j - 1];
    }

    // 插入新数据到第 i 位
    (*L).data[i] = e;

    return OK;
}

/**
 * 从线性表 L 删除第 i 个元素，保存其值到 *e
 *
 * @param L 要操作的线性表
 * @param i 要删除的下标
 * @param e 要保存的元素
 * @return 1-成功 0-失败
 */
Status ListDelete(List *L, int i, ElemType *e)
{
    if (i < 0 || i > (*L).length - 1) {
        printf("ListDelete: %d out of range.\n", i);
        return ERROR;
    }

    // 保存要删除的元素
    *e = (*L).data[i];

    // 线性表前移
    for (int j = i; j < (*L).length; ++j) {
        (*L).data[j] = (*L).data[j + 1];
    }

    // 长度减少
    (*L).length--;

    return OK;
}

int main()
{
    // 初始化线性表并打印
    List L;
    InitList(&L);
    dump(L);

    // 插入元素测试
    ListInsert(&L, 0, 2);
    dump(L);
    ListInsert(&L, 0, 4);
    dump(L);
    ListInsert(&L, 1, 5);
    dump(L);
    ListInsert(&L, 1, 7);
    ListInsert(&L, 1, 8);
    dump(L);
    ListInsert(&L, 1, 12);
    dump(L);

    // 删除元素测试
    ElemType e;
    ListDelete(&L, 1, &e);
    printf("delete L[%d] = %d\n", 1, e);
    dump(L);
    ListDelete(&L, 0, &e);
    ListDelete(&L, 0, &e);
    ListDelete(&L, 0, &e);
    dump(L);
    ListDelete(&L, 0, &e);
    dump(L);

    return 0;
}

