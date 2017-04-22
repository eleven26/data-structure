//
// Created by ruby on 4/21/17.
//

#include "linear_list.h"
#include <stdio.h>
#include <stdlib.h>

//初始化线性表，长度初始化为0，元素列表设为空
Status InitList(LinearList* linearList)
{
    linearList->length = 0;
    linearList->elements = (Element*)0;
    return SUCCESS;
}

//销毁线性表，长度设置为0，清空元素数组
Status DestroyList(LinearList* linearList)
{
    if (!linearList) {
        return FAIL;
    }
    linearList->length = 0;
    linearList->elements = (Element*)0;
    return SUCCESS;
}

//判断线性表是否为空
Status ListEmpty(LinearList linearList)
{
    if (!linearList) {
        return FAIL;
    }
    return linearList.length == 0 ? TRUE : FALSE;
}

//返回线性表长度
size_t ListLength(LinearList linearList)
{
    if (!linearList) {
        return FAIL;
    }
    return linearList.length;
}

//获取线性表中位置为position的元素
Status GetElement(LinearList linearList, size_t position, ElementType* e)
{
    if (!linearList) {
        return FAIL;
    }
    if (position < 1 || position > linearList.length) {
        printf("index out of range.\n");
        exit(-1);
    }

    *e = linearList.elements[position-1];
    return SUCCESS;
}

//定位满足compare的元素
Status LocateElement(LinearList linearList,
                          ElementType e,
                          ElementType* result,
                          int compare(ElementType, ElementType))
{
    if (!linearList) {
        return FAIL;
    }
    for (int i = 0; i < linearList.length; ++i) {
        if (compare(e, linearList.elements[i]) == 0) {
            //compare返回0的时候表示满足条件
            *result = linearList.elements[i];
            return SUCCESS;
        }
    }

    return FAIL;
}

//获取元素值为current_element的前一个元素
Status PriorElement(LinearList linearList,
                    ElementType current_element,
                    ElementType* previous_element)
{
    if (!linearList) {
        return FAIL;
    }

    for (int i = 0; i < linearList.length; ++i) {
        if (i == 0 && linearList.elements[i] == current_element) {
            return FAIL;
        }

        if (linearList.elements[i] == current_element) {
            previous_element = linearList.elements[i-1];
            return SUCCESS;
        }
    }

    return FAIL;
}

//获取元素值为current_element的下一个元素
Status NextElement(LinearList linearList,
                   ElementType current_element,
                   ElementType* next_element)
{
    if (!linearList) {
        return FAIL;
    }

    for (int i = 0; i < linearList.length; ++i) {
        if (i == linearList.length -1 && linearList.elements[i] == current_element) {
            return FAIL;
        }

        if (linearList.elements[i] == current_element) {
            next_element = linearList.elements[i+1];
            return SUCCESS;
        }
    }

    return FAIL;
}

//在位置position(1, length)插入元素element
//position之后的元素后移
Status ListInsert(LinearList linearList, size_t position, ElementType element)
{
    if (!linearList) {
        return FAIL;
    }

    if (position < 1 || position > linearList.length) {
        printf("index out of range.\n");
        return FAIL;
    }

    ElementType *newElements = (ElementType*)calloc(linearList.length + 1, sizeof(ElementType));
    if (!newElements) {
        printf("allocate memory fail!\n");
        exit(-1);
    }

    //position的前后元素采用内存复制的形式
    memcpy(newElements, linearList.elements, position-1);
    newElements[position] = element;
    memcpy(newElements + position, linearList.elements + position, linearList.length - position);

    return SUCCESS;
}

//删除位置为position的元素
Status ListDelete(LinearList linearList, size_t position, ElementType* element)
{
    if (!linearList || linearList.length == 0) {
        return FAIL;
    }

    if (position < 1 || position > linearList.length) {
        printf("index out of range.\n");
        exit(-1);
    }

    ElementType *newElements = (ElementType*)calloc(linearList.length - 1, sizeof(ElementType));
    if (!newElements) {
        printf("allocate memory fail!\n");
        exit(-1);
    }

    //position的前后元素采用内存复制的形式
    memcpy(newElements, linearList.elements, position-1);
    memcpy(newElements + position, linearList.elements + position, linearList.length - position);

    return SUCCESS;
}

//使用函数visit遍历线性表中的元素
Status ListTraverse(LinearList linearList, void visit(ElementType))
{
    if (!linearList) {
        return FAIL;
    }

    for (int i = 0; i < linearList.length; ++i) {
        visit(linearList.elements[i]);
    }

    return SUCCESS;
}