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
    L = (List*)malloc(sizeof(L));

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

    for (int i = 0; i < L.length; ++i) {
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
Status ListInsert(List L, int i, ElemType e)
{
    ElemType temp;

    // 临界条件判断
    if (i < 0 || i > L.length) {
        printf("ListInsert: index out of range.\n");
        return ERROR;
    }

    // 从 i 开始往后移动
    // 边界：最后一位
    for (int j = L.length - 1; j > i; --j) {
    }

    // 插入新数据到第 i 位
    L.data[i] = e;
    L.length++;

    return OK;
}

int main()
{
    // 初始化线性表并打印
    List L;
    InitList(&L);
    dump(L);

    return 0;
}

