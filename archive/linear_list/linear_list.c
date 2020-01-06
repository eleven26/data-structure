//
// Created by ruby on 4/21/17.
//

#include "linear_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化线性表，长度初始化为0，元素列表设为空
Status InitList(LinearList *linearList, size_t length)
{
    linearList->length = length;
    linearList->real_length = 0;
    if (length != 0) {
        linearList->specific_length = TRUE;
    }
    linearList->elements = (ElementType *) calloc(linearList->length, sizeof(ElementType));
    if (!linearList->elements) {
        return FAIL;
    }
    return SUCCESS;
}

// 销毁线性表，长度设置为0，清空元素数组
Status DestroyList(LinearList *linearList)
{
    if (!linearList) {
        return FAIL;
    }
    linearList->length = 0;
    linearList->elements = (ElementType *)0;
    return SUCCESS;
}

//清空线性表
Status ClearList(LinearList *linearList)
{
    if (!linearList) {
        return FAIL;
    }

    linearList->length = 0;
    linearList->elements = (ElementType*)0;

    return SUCCESS;
}

//判断线性表是否为空
Status ListEmpty(LinearList *linearList)
{
    if (!linearList) {
        return FAIL;
    }
    return linearList->length == 0 ? TRUE : FALSE;
}

//返回线性表长度
size_t ListLength(LinearList *linearList)
{
    if (!linearList) {
        return FAIL;
    }
    return linearList->length;
}

//获取线性表中位置为position的元素
Status GetElement(LinearList *linearList, size_t position, ElementType *e)
{
    if (!linearList) {
        return FAIL;
    }
    if (position < 1 || position > linearList->length) {
        printf("index out of range.\n");
        exit(-1);
    }

    *e = linearList->elements[position-1];
    return SUCCESS;
}

//定位满足compare的元素
Status LocateElement(LinearList *linearList,
                          ElementType e,
                          size_t *position,
                          int compare(ElementType, ElementType))
{
    if (!linearList) {
        return FAIL;
    }
    for (int i = 0; i < linearList->length; ++i) {
        if (compare(e, linearList->elements[i])) {
            //compare返回TRUE的时候表示满足条件
            *position = i + 1;
            return SUCCESS;
        }
    }

    return FAIL;
}

//获取元素值为current_element的前一个元素
Status PriorElement(LinearList *linearList,
                    ElementType current_element,
                    ElementType *previous_element)
{
    if (!linearList) {
        return FAIL;
    }

    for (int i = 0; i < linearList->length; ++i) {
        if (i == 0 && linearList->elements[i] == current_element) {
            return FAIL;
        }

        if (linearList->elements[i] == current_element) {
            *previous_element = linearList->elements[i-1];
            return SUCCESS;
        }
    }

    return FAIL;
}

//获取元素值为current_element的下一个元素
Status NextElement(LinearList *linearList,
                   ElementType current_element,
                   ElementType *next_element)
{
    if (!linearList) {
        return FAIL;
    }

    for (int i = 0; i < linearList->length; ++i) {
        if (i == linearList->length -1 && linearList->elements[i] == current_element) {
            return FAIL;
        }

        if (linearList->elements[i] == current_element) {
            *next_element = linearList->elements[i+1];
            return SUCCESS;
        }
    }

    return FAIL;
}

//在位置position(1, length)插入元素element
//position之后的元素后移
Status ListInsert(LinearList *linearList, size_t position, ElementType element)
{
    if (!linearList) {
        return FAIL;
    }

    if (position < 1 || (position > 1 && position > linearList->length)) {
        printf("index out of range.\n");
        return FAIL;
    }

    ElementType *newElements = (ElementType*)calloc(linearList->length + 1, sizeof(ElementType));
    if (!newElements) {
        printf("allocate memory fail!\n");
        exit(-1);
    }

    if (linearList->specific_length) {
        linearList->elements[position - 1] = element;
    } else {
        // position的前后元素采用内存复制的形式
        size_t insert_position = position - 1;
        memcpy(newElements, linearList->elements, insert_position * sizeof(ElementType));
        newElements[insert_position] = element;
        memcpy(newElements + position, linearList->elements + insert_position,
               (linearList->length - insert_position) * sizeof(ElementType));

        //linearList的elements指向新分配的数组, 线性表长度加1
        linearList->elements = newElements;
        ++linearList->length;
    }
    ++linearList->real_length;

    if (linearList->length == linearList->real_length) {
        linearList->specific_length = FALSE;
    }

    return SUCCESS;
}

//删除位置为position的元素
Status ListDelete(LinearList* linearList, size_t position, ElementType *element)
{
    if (!linearList || linearList->length == 0) {
        return FAIL;
    }

    if (position < 1 || (position > 1 && position > linearList->length)) {
        printf("index out of range.\n");
        exit(-1);
    }

    ElementType *newElements = (ElementType*)calloc(linearList->length - 1, sizeof(ElementType));
    if (!newElements) {
        printf("allocate memory fail!\n");
        exit(-1);
    }

    *element = linearList->elements[position-1]; //位置1的时候下标是0

    //position的前后元素采用内存复制的形式
    size_t delete_position = position - 1;
    memcpy(newElements, linearList->elements, delete_position * sizeof(ElementType));
    memcpy(newElements + delete_position, linearList->elements + position, (linearList->length - position) * sizeof(ElementType));

    //linearList的elements指向新分配的数组, 线性表长度减1
    linearList->elements = newElements;
    --linearList->length;

    return SUCCESS;
}

//使用函数visit遍历线性表中的元素
Status ListTraverse(LinearList* linearList, Status visit(ElementType))
{
    if (!linearList) {
        return FAIL;
    }

    for (int i = 0; i < linearList->length; ++i) {
        if (visit(linearList->elements[i]) == FALSE) {
            printf("visit fail.\n");
            exit(1);
        }
    }

    return SUCCESS;
}

// 把一个线性表拆分成两个线性表, [0, position), [position, linearList->length)
Status DivideLinearList(LinearList *linearList,
                        size_t position,
                        LinearList *linearList1,
                        LinearList *linearList2)
{
    if (!linearList || !linearList1 || !linearList2) {
        return FAIL;
    }

    if (position < 1 || position >= linearList->length) {
        printf("index out of range.\n");
        exit(-1);
    }

    for (int i=0; i<position; ++i) {
        linearList1->elements[i] = linearList->elements[i];
    }

    for (int j = position; j < linearList->length; ++j) {
        linearList2->elements[j-position] = linearList->elements[j];
    }

    return SUCCESS;
}

// 打印线性表(遍历输出线性表元素)
void PrintList(LinearList *linearList)
{
    if (!linearList) {
        printf("请使用有效的线性表参数\n");
        exit(-1);
    }

    for (int i = 0; i < linearList->length; ++i) {
        if (i < linearList->length - 1) {
            printf("%d, ", linearList->elements[i]);
        } else {
            printf("%d\n", linearList->elements[i]);
        }
    }
}

// 克隆一个线性表
Status CloneLinearList(LinearList *linearList, LinearList *newLinearList)
{
    if (!linearList || !newLinearList) {
        printf("请使用有效的线性表参数\n");
        exit(1);
    }

    if (linearList->length != newLinearList->length) {
        printf("线性表长度不正确\n");
        exit(2);
    }

    for (int i = 0; i < linearList->length; ++i) {
        newLinearList->elements[i] = linearList->elements[i];
    }

    return SUCCESS;
}

// union操作，把只存在linearList2中而不存在linearList1中的元素插入到linearList1中
Status UnionLinearList(LinearList *linearList1, LinearList *linearList2)
{
    if (!linearList1 || !linearList2) {
        printf("请使用有效的线性表参数\n");
        exit(1);
    }

    size_t position = -1;
    for (int i = 0; i < linearList2->length; ++i) {
        LocateElement(linearList1, linearList2->elements[i], &position, equal);
        if (position == -1) { // 在linearList1中找不到linearList2的元素
            ListInsert(linearList1, 1, linearList2->elements[i]);
        } else {
            position = -1;
        }
    }

    return SUCCESS;
}

// 判断两个元素是否相等
Status equal(ElementType e1, ElementType e2)
{
    return (e1 == e2 ? 1 : 0);
}

// 合并两个数据元素按值非递减有序排列的线性表
Status MergeOrderedLinearList(LinearList *linearList1, LinearList *linearList2, LinearList *mergedLinearList)
{
    if (!linearList1 || !linearList2) {
        printf("请使用有效的线性表参数\n");
        exit(1);
    }

    if (mergedLinearList->length != (linearList1->length + linearList2->length)) {
        printf("合并的线性表长度不匹配\n");
        exit(2);
    }

    ElementType e;
    size_t index = 0, index1 = 0, index2 = 0;
    while (index1 < linearList1->length && index2 < linearList2->length) {
        if (linearList1->elements[index1] <= linearList2->elements[index2]) {
            ListInsert(mergedLinearList, ++index, linearList1->elements[index1++]);
        } else {
            ListInsert(mergedLinearList, ++index, linearList2->elements[index2++]);
        }
    }

    while (index1 < linearList1->length) {
        ListInsert(mergedLinearList, ++index, linearList1->elements[index1++]);
    }

    while (index2 < linearList2->length) {
        ListInsert(mergedLinearList, ++index, linearList2->elements[index2++]);
    }

    return SUCCESS;
}