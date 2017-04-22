//
// Created by ruby on 4/21/17.
//

#ifndef DATA_STRUCTURE_LINEAR_LIST_H
#define DATA_STRUCTURE_LINEAR_LIST_H

#endif //DATA_STRUCTURE_LINEAR_LIST_H

#include "../common.h"
#include <sys/types.h>

#ifndef LINEAR_LIST_ELEMENT_TYPE
#define LINEAR_LIST_ELEMENT_TYPE
typedef int ElementType;
#endif

/**
 * 线性表
 * elements 线性表元素数组
 * length   线性表长度
 */
typedef struct {
    ElementType *elements;
    size_t length;
} LinearList;

/**
 * 构造一个空的线性表linearList
 * @param linearList 线性表
 * @return
 */
Status InitList(LinearList *linearList);

/**
 * 销毁线性表linearList (前提: 线性表存在)
 * @param linearList 线性表
 * @return
 */
Status DestroyList(LinearList *linearList);

/**
 * 将linearList置为空表
 * @param linearList 线性表
 * @return
 */
Status ClearList(LinearList *linearList);

/**
 * 若linearList为空表, 返回TRUE, 否则返回FALSE (前提: 线性表存在)
 * @param linearList 线性表
 * @return
 */
Status ListEmpty(LinearList *linearList);

/**
 * 返回linearList中数据元素个数 (前提: 线性表存在)
 * @param linearList 线性表
 * @return
 */
size_t ListLength(LinearList *linearList);

/**
 * 用element返回linearList中第position个数据元素的值
 * (前提: 线性表存在, 1<=position<=ListLength(linearList) )
 * @param linearList 线性表
 * @param position 需要获取元素的下标
 * @param element 保存位置为position的值
 * @return
 */
Status GetElement(LinearList *linearList, size_t position, ElementType* element);

/**
 * 返回linearList中第一个与element满足关系compare()的数据元素的位置。若这样的数据元素不存在，则返回值为-1
 * (前提: 线性表linearList存在，compare()是数据元素判定函数)
 * @param linearList 线性表
 * @param element 需要与之比较的元素
 * @param compare 使用来比较的函数的函数指针(返回0的时候表示满足条件)
 * @return
 */
Status LocateElement(LinearList *linearList,
                          ElementType element,
                          size_t *result,
                          int compare(ElementType, ElementType));

/**
 * 若current_element是linearList的数据元素，且不是第一个，
 * 则用previous_element返回它的前驱，否则操作失败，previous_element无定义。
 * (前提: 线性表已存在)
 * @param linearList 线性表
 * @param current_element 返回值为current_element的前一个数据元素
 * @param previous_element
 * @return
 */
Status PriorElement(LinearList *linearList, ElementType current_element, ElementType* previous_element);

/**
 * 若current_element是linearList的数据元素，且不是最后一个，
 * 则用next_element返回它的后继，否则操作失败，next_element无定义。
 * (前提: 线性表已存在)
 * @param linearList 线性表
 * @param current_element
 * @param next_element
 * @return
 */
Status NextElement(LinearList *linearList, ElementType current_element, ElementType* next_element);

/**
 * 在linearList中第position个位置之前插入新的数据元素，linearList的长度加1。
 * (前提: 线性表linearList已存在，1<=position<=ListLength(linearList)+1 )
 * @param linearList 线性表
 * @param position
 * @param element
 * @return
 */
Status ListInsert(LinearList *linearList, size_t position, ElementType element);

/**
 * 删除linearList的第position个数据元素，并且用element返回其值，linearList的长度减1。
 * (前提: 线性表linearList已存在且非空，1<=position<=ListLength(linearList) )
 * @param linearList
 * @param position
 * @param element
 * @return
 */
Status ListDelete(LinearList *linearList, size_t position, ElementType* element);

/**
 * 依次对linearList的每个数据元素调用函数visit()。一旦visit()失败，则操作失败。
 * @param linearList
 * @param visit
 * @return
 */
Status ListTraverse(LinearList *linearList, void visit(ElementType));