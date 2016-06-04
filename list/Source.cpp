#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "list.h"

void reMalloc(struct SeqList *L, int newSize){
	//重新分配线性表内存，大小为newSize
	node *new_List =(node *) calloc(L->maxSize , sizeof(node));  //分配临时内存块
	memcpy(new_List, L->list, L->maxSize * sizeof(node));  //这里的长度应该是L->maxSize * sizeof(node)，而不是L->maxSize
	free(L->list);
	L->list = NULL;

	int tmp_size = L->maxSize;
	L->list = (node *) calloc(newSize , sizeof(node)); //申请新的内存
	memcpy(L->list, new_List, L->maxSize * sizeof(node));
	L->maxSize = newSize;
	free(new_List);
	new_List = NULL;

	for (int i = tmp_size; i < L->maxSize; i++)
	{
		L->list[i].is_used = 0; //每个元素都标志为未使用
	}
}//reMalloc

Status InitList(struct SeqList *L, int maxSize){
	//构造一个空的线性表
	if (maxSize < 0){
		printf("maxSize错误!");
		exit(1);
	}
	L->list = (node*) calloc(maxSize, sizeof(node));
	for (int i = 0; i < maxSize; i++)
	{
		L->list[i].is_used = 0; //每个元素都标志为未使用
	}
	L->size = 0;
	L->maxSize = maxSize;
	return OK;
}//InitList

Status DestroyList(struct SeqList *L){
	//销毁列表
	free(L->list);
	L->size = 0;
	L->maxSize = 0;
	L->list = NULL;
	return OK;
}//DestroyList

Status ClearList(struct SeqList *L){
	//将L重置为空表，清除L中的所有元素，释放存储空表
	L->maxSize = 0;
	L->size = 0;
	if (L->list != NULL){
		free(L->list);
		L->list = 0;
		L->size = L->maxSize = 0;
	}
	return OK;
}//ClearList

Status ListEmpty(struct SeqList *L){
	//若L为空表，则返回TRUE，否则返回FALSE
	return L->size == 0 ? TRUE : FALSE;
}//ListEmpty

int ListLength(struct SeqList *L){
	//返回当前线性表的长度
	return L->maxSize;
}//ListLength

ElemType GetElem(struct SeqList *L, int pos){
	//返回线性表中位置pos的元素
	if (pos<1 || pos>L->maxSize){
		printf("元素序号越界");
		return OVERLOW;
	}
	if (L->list[pos - 1].is_used = 0){
		printf("该位置没有元素！");
		return ERROR;
	}
	return L->list[pos - 1].value;
}//GetElem

void MoveList(struct SeqList *L, int pos){
	//将线性表L从pos位置开始向后移
	for (int i = L->maxSize - 1; i > pos; i--)
	{	/*i>pos而不是i>=pos，由于L->list[pos].is_used = 1
		//当i=pos+1时，会把list[pos]向后移动一位，这样list[pos]就可以容纳新元素了
		//而如果取i=pos的话，会使得L->list[pos].is_used变成1，就不能插入新元素了
		*/
		//最大下标是L->maxSize - 1
		//每个元素后移，从最后一个元素开始移动，将每个可以移动的元素都移动
		if (L->list[i].is_used == 0 && L->list[i - 1].is_used == 1){
			//如果正在使用的话会被覆盖
			L->list[i].value = L->list[i - 1].value;
			L->list[i].is_used = L->list[i - 1].is_used;
			L->list[i - 1].is_used = 0; //i-1位置的元素已经移动到i位置
		}
	}
}//MoveList

Status PutElem(struct SeqList *L, int pos, ElemType e){
	//在位置pos插入元素e，位置pos之后都要后移，1<= pos <= L-maxSize
	pos = pos - 1;
	if (pos<0 || pos>L->maxSize - 1){
		printf("非法位置参数\n");
		return OVERLOW;
	}
	if (L->size == L->maxSize){
		printf("线性表已经不能容纳更多元素");
		return OVERLOW;
	}else{
		if (L->list[pos].is_used == 0){
			L->list[pos].is_used = 1;
			L->list[pos].value = e;
			L->size = L->size + 1;
		}
		else{
			MoveList(L, pos);
			if (L->list[pos].is_used == 0){
				L->list[pos].is_used = 1;
				L->list[pos].value = e;
				L->size = L->size + 1;
			}
			else{
				printf("线性表该位置%d无法插入\n", pos);
				return OVERLOW;
			}
		}
		return OK;
	}
}//PutElem

Status UpdatePosElem(struct SeqList *L, int pos, ElemType e){
	//直接替换线性表位置pos的元素，而不改变其他元素的位置
	L->list[pos - 1].value = e;
	L->list[pos - 1].is_used = 1;
	return OK;
}//UpdatePosElem

void InsertFirstList(struct SeqList *L, ElemType e){
	//向线性表L的表头插入元素e
	if (L->list[L->maxSize - 1].is_used == 1){
		reMalloc(L, L->maxSize + 1);
	}
	MoveList(L, 0);
	L->list[0].value = e;
	L->list[0].is_used = 1;
}//InsertFirstList

void InsertLastList(struct SeqList *L, ElemType e){
	//向线性表L的表尾插入元素e
	if (L->list[L->maxSize - 1].is_used == 1){
		reMalloc(L, L->maxSize + 1);
	}
	L->list[L->maxSize - 1].value = e;
	L->list[L->maxSize - 1].is_used = 1;
}//InsertLastList

ElemType deleteElem(struct SeqList *L, int pos){
	//删除位置pos的元素
	if (L->size == 0){
		printf("线性表为空!\n");
		return ERROR;
	}
	if (L->list[pos].is_used == 1){
		ElemType temp = L->list[pos].value;
		L->list[pos].value = 0;
		L->list[pos].is_used = 0;
		L->size--;
		return temp;
	}
	else
	{
		printf("该位置没有元素\n");
		return ERROR;
	}
	
}//deleteElem

ElemType deleteFirstList(struct SeqList *L){
	//从线性表L中删除表头元素并返回它，若删除失败返回错误代码
	return deleteElem(L, 0);
}//deleteFirstList

ElemType deleteLastList(struct SeqList *L){
	//从线性表L中删除表尾元素并返回它，若删除失败返回错误代码
	int pos = L->maxSize - 1;
	return deleteElem(L, pos);
}//deleteLastList

ElemType deletePosList(struct SeqList *L, int pos){
	//从线性表L中删除位置pos的元素
	pos = pos - 1;
	return deleteElem(L, pos);
}//deletePosList

Status visit(ElemType e){
	return e > 10 ? TRUE : FALSE;
}

void traverseList(struct SeqList *L){
	//普通遍历，打印线性表存储有值的元素
	for (int i = 0; i < L->maxSize; i++){
		if (L->list[i].is_used == 1){
			printf("L[%d]=%d, ", i, L->list[i].value);
		}
		if (i == L->maxSize - 1){
			printf("\n");
		}
	}
}//traverseList

Status ListTraverse(struct SeqList *L, Status visit(ElemType e)){
	//依次对L的每个数据元素调用函数visit，一旦visit()失败，则操作失败。
	for (int i = 0; i < L->maxSize; i++){
		if (L->list[i].is_used == 1 && visit(L->list[i].value)){
			return FALSE;
		}
	}
	return TRUE;
}//ListTraverse

int FindList(struct SeqList *L, ElemType e){
	//从线性表中查找值与e相等的元素，若查找成功返回其位置，否则返回-1
	//如果有重复元素只是返回第一个出现的位置
	for (int i = 0; i < L->maxSize; i++)
	{
		if (L->list[i].is_used == 1 && L->list[i].value == e){
			return i;
		}
	}
	return -1;
}//FindList

Status compare(ElemType e, ElemType e1){
	return e<e1 ? TRUE : FALSE;
}

int LocateElem(struct SeqList *L, ElemType e, Status compare(ElemType e, ElemType e1)){
	//返回L中第一个与e满足关系compare()的数据元素的位置
	//若这样的元素不存在，则返回-1
	for (int i = 0; i < L->maxSize; i++){
		if (L->list[i].is_used == 1 && compare(e, L->list[i].value)){
			return i;
		}
	}
	return -1;
}//LocateElem

ElemType PriorElem(struct SeqList *L, int pos){
	//若pos有数据元素，且不是第一个，则返回它的前驱，否则操作失败
	if (L->size>1 && pos != 0){
		if (L->list[pos - 1].is_used == 1){
			return L->list[pos - 1].value;
		}
		else
		{
			printf("该元素前驱元素为空!\n");
			return 0;
		}
	}
	return ERROR;
}//PriorElem

ElemType NextElem(struct SeqList *L, int pos){
	//若pos有数据元素，且不是最后一个，则返回它的后继，否则操作失败
	if (L->size>1 && pos < L->maxSize-1){
		if (L->list[pos + 1].is_used == 1){
			return L->list[pos + 1].value;
		}
		else
		{
			printf("该元素后继元素为空!\n");
			return 0;
		}
	}
	return ERROR;
}//NextElem


int main(){
	struct SeqList L;
	InitList(&L, 10);
	SeqList *J = &L;

	reMalloc(&L, 20);

	Status state = PutElem(&L,11,10);
	printf("insert test list[%d]=: %d\n", 10, J->list[10].value);
	printf("is used? %d\n", J->list[10].is_used);

	Status state1 = PutElem(&L, 9, 20);
	printf("insert test list[%d]=: %d\n", 8, J->list[8].value);
	printf("is used? %d\n", J->list[8].is_used);

	InsertFirstList(&L, 21);
	InsertLastList(&L, 22);
	deleteElem(&L, 10);

	printf("insert test list[%d]=: %d\n", 0, J->list[0].value);

	Status state2 = PutElem(&L, 11, 10);
	printf("insert test list[%d]=: %d\n", 10, J->list[10].value);
	printf("is used? %d\n", J->list[10].is_used);

	printf("10的位置:%d\n", FindList(&L, 10));

	traverseList(&L);
	
	printf("new size:%d\n",J->maxSize);
	//traverseList(&L);
	printf("maxSize:%d\n", J->size);
	printf("遍历结果:%d\n", ListTraverse(&L,visit));

	printf("大于21的第一个元素位置 %d\n", LocateElem(&L, 21, compare));

	printf("位置11的前驱元素为:%d\n", PriorElem(&L, 1));

	printf("sizeof(L)=%d\n", sizeof(L)); 
	//L始终等于4的原因是，当L作为参数传递的时候，"退化"为指针，sizeof只能得到指针对应类型的长度.
	
	
	
	getchar();
	return 0;
}