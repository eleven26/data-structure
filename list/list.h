#include "common.h"

typedef int ElemType;
struct node{
	ElemType value; //元素的值
	int is_used; //1表示正在使用，0表示空闲
};

struct SeqList
{
	node *list;
	int size;  //记录当前长度
	int maxSize; //记录最大可容纳的长度
};

void reMalloc(struct SeqList *L, int newSize);
//重新分配线性表内存

Status InitList(struct SeqList *L, int MaxSize);
//构造一个空的线性表

Status Destroy(struct SeqList *L);
//销毁线性表L

Status ClearList(struct SeqList *L);
//将L重置为空表

Status ListEmpty(struct SeqList *L);
//若L为空表，则返回TRUE，否则返回FALSE

int ListLength(struct SeqList *L);
//返回L中元素的个数

ElemType GetElem(struct SeqList *L, int pos);
//用e返回L中第i个数据元素的值

Status PutElem(struct SeqList *L, int pos, ElemType e);
//在位置i插入元素e

Status ListTraverse(struct SeqList *L, Status visit(ElemType e));
//依次对L的每个数据元素调用函数visit，一旦visit()失败，则操作失败。

int FindList(struct SeqList *L, ElemType e);
//从线性表中查找值与e相等的元素，若查找成功返回其位置，否则返回-1

Status UpdatePosElem(struct SeqList *L, int pos, ElemType e);
//直接替换线性表位置pos的元素，而不改变其他元素的位置

Status InsertElem(struct SeqList *L, ElemType e);
//遍历线性表，如果有空闲位置则插入，没有则重新分配内存再插入

void InsertFirstList(struct SeqList *L, ElemType e);
//向线性表L的表头插入元素e

void InsertLastList(struct SeqList *L, ElemType e);
//向线性表L的表尾插入元素e

ElemType deleteElem(struct SeqList *L, int pos);
//删除位置pos的元素

ElemType deleteFirstList(struct SeqList *L);
//从线性表L中删除表头元素并返回它，若删除失败返回错误代码

ElemType deleteLastList(struct SeqList *L);
//从线性表L中删除表尾元素并返回它，若删除失败返回错误代码

ElemType deletePosList(struct SeqList *L, int pos);
//从线性表L中删除位置pos的元素

int LocateElem(struct SeqList *L, ElemType e, Status(*compare));
//返回L中第一个与e满足关系compare()的数据元素的位置
//若这样的元素不存在，则返回-1

ElemType PriorElem(struct SeqList *L, int pos);
//若pos有数据元素，且不是第一个，则返回它的前驱，否则操作失败

ElemType NextElem(struct SeqList *L, int pos);
//若pos有数据元素，且不是最后一个，则返回它的后继，否则操作失败

void UnionList(struct SeqList *LA, struct SeqList LB);
//将所有在线性表LB中但不在LA中的数据元素插入到LA中
