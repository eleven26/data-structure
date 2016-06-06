#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "link_list.h"

void initList(LinkList *L){
	/*初始化链表，即将单链表的表头指针设为空*/
	*L = NULL;
	return;
}

void clearList(LinkList *L){
	/*清除链表中的所有元素，释放所有结点，使之成为一个空表*/
	node *cur_node, *next_node;
	cur_node = *L;
	/*遍历单链表，依次释放每个结点*/
	while (cur_node!=NULL)
	{
		next_node = cur_node->next; /*保存下一个结点的指针*/
		free(cur_node);
		cur_node = next_node;
	}
	*L = NULL;
	return;
}

int sizeList(LinkList *L){
	/*返回单链表的长度*/
	int count = 0;
	while (*L!= NULL)
	{
		count++;
		*L = (*L)->next;
	}
	return count;
}

int emptyList(LinkList *L){
	/*检查单链表是否为空，空则返回1，否则返回0*/
	return *L == NULL ? 1 : 0;
}

ElemType getElem(LinkList L, int pos){
	/*返回链表中第pos个结点的元素*/
	int i = 0;
	if (pos < 1){
		printf("位置非法!");
	}
	while (L != NULL)
	{
		i++;
		if (i == pos){
			break;
		}
		L = L->next;
	}
	if (L != NULL){
		return L->data;
	}
	else
	{
		printf("位置非法!");
	}
	return -1;
}

void traverseList(LinkList *L){
	/*遍历一个单链表*/
	int i = 1;
	while (*L != NULL)
	{
		printf("L[%d]=%d,", i, (*L)->data);
		i++;
		*L = (*L)->next;
	}
	return;
}

ElemType* findList(LinkList *L, ElemType e){
	/*从单链表中查找值为e的第一个元素，查找到则返回地址*/
	while (*L != NULL)
	{
		if ((*L)->data == e){
			return &((*L)->data);
		}
		else
		{
			*L = (*L)->next;
		}
	}
	return NULL;
}

int updateList(LinkList *L, int pos, ElemType e){
	/*把单链表中pos位置的值修改为e，成功返回1，否则返回0*/
	int i = 0;
	while (*L!=NULL)
	{
		i++;
		if (i == pos){
			(*L)->data = e;
			return 1;
		}
		else
		{
			*L = (*L)->next;
		}
	}
	return 0;
}

void insertFirstList(LinkList *L, ElemType e){
	//node* L与node **L，node* L的时候，L是一个node结点，而node **L的时候，L是一个指向node的地址
	//node* Node表示Node是指向node结点的地址
	/*向单链表表头插入一个元素*/
	node* new_node;
	new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("内存分配失败");
		exit(1);
	}
	else
	{
		new_node->data = e;
		new_node->next = *L;
		*L = new_node;
	}
	return;
}

void insertLastList(LinkList *L, ElemType e){
	/*向单链表的末尾添加一个元素*/
	node* new_node;
	new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("内存分配失败!\n");
		exit(1);
	}
	/*把e赋给新节点的data域，把空值赋值给新节点的next*/
	new_node->data = e;
	new_node->next = NULL;
	/*若原表为空表，则作为表头插入*/
	if (*L == NULL){
		*L = new_node;
	}
	else
	{
		/*找到尾节点并完成插入*/
		node* p = *L;
		while (p->next != NULL){
			p = p->next;
		}
		p->next = new_node;
	}
	return;
}

int insertPosList(LinkList *L, int pos, ElemType e){
	/*向单链表中第pos个结点位置插入元素为x的节点，若插入成功返回1，否则返回-1*/
	int i = 0;
	node * p = *L,*ap = NULL;
	node * new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("内存分配失败!\n");
		return -1;
	}
	/*对pos非法的进行处理*/
	if (pos <= 0){
		printf("pos位置非法!\n");
		return -1;
	}
	/*查找第pos个结点*/
	while (p!=NULL)
	{
		i++;
		if (pos == i){
			break;
		}
		ap = p; //当前指针
		p = p->next; //下一个指针
	}
	if (pos == i){
		//将p替换为new_node
		new_node->data = e;
		new_node->next = p;
		if (ap == NULL){//插入表头
			p = new_node;
		}
		else{
			ap->next = new_node;
		}
		return 0;
	}
	else{
		printf("位置超出链表长度!\n");
		return -1;
	}
}

void insertOrderList(LinkList *L, ElemType e){
	/*向有序链表中插入元素e结点，使得插入后仍然有序*/
	node *p = *L, *ap = NULL;
	node *new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("内存分配失败!\n");
		exit(1);
	}
	new_node->data = e;
	/*如果链表没有元素*/
	if (p == NULL || e < p->data){
		new_node->next = p;
		p = new_node;
		return;
	}
	/*顺序查找出e结点的插入位置*/
	while (p!=NULL)
	{
		if (e <= p->data){
			break;
		}
		ap = p;
		p = p->next;
	}
	new_node->next = p;
	ap->next = new_node;
	return;
}

ElemType deleteFirstList(LinkList *L){
	/*从单链表中删除表头结点，并把该结点的值返回，若删除失败停止运行*/
	ElemType temp;
	node *p = *L;
	if (p == NULL){
		printf("链表为空!\n");
		exit(1);
	}
	temp = p->data;
	*L = (*L)->next;
	free(p); /*回收被删除的表头结点*/
	return temp;
}

ElemType deleteLastList(LinkList *L){
	/*从单链表中删除表尾结点并返回它的值，删除失败则退出*/
	ElemType temp;
	node *p = *L, *ap = NULL;
	if (p == NULL){
		printf("单链表为空!\n");
		exit(1);
	}
	while (p->next != NULL)
	{
		ap = p;
		p = p->next;
	}
	if (ap == NULL){
		/*只有一个结点*/
		*L = NULL;
		return -1;
	}
	else
	{
		ap->next = NULL;
	}
	temp = p->data;
	free(p);
	return temp;
}

ElemType deletePosList(LinkList *L, int pos){
	/*从单链表删除第pos个结点并返回它的值，删除失败退出*/
	int i = 0;
	ElemType temp;
	node *p = *L, *ap = NULL;
	if ((p == NULL) || (pos <= 0)){
		printf("链表为空或者pos不正确!\n");
		exit(1);
	}
	while (p!=NULL)
	{
		i++;
		if (i == pos){
			break;
		}
		ap = p;
		p = p->next;
	}
	if (p == NULL){
		printf("pos不正确!\n");
		exit(1);
	}
	if (pos == 1){
		/*pos==1的时候*/
		temp = p->data;
		*L = (*L)->next;
		free(p);
		return temp;
	}
	else
	{
		ap->next = p->next;
		temp = p->data;
		free(p); /*释放被删除结点的内存*/
		return temp;
	}
}

int deleteValueList(LinkList *L, ElemType e){
	/*从单链表中删除值为e的第一个节点，成功返回1，失败返回-1*/
	node *p = *L, *ap = NULL;
	/*从单链表中查找值为e的结点*/
	while (p!=NULL)
	{
		if (p->data == e){
			break;
		}
		ap = p;
		p = p->next;
	}
	if (p == NULL){
		/*若查找失败，则返回-1*/
		return -1;
	}
	if (ap == NULL){
		/*如果删除的是表头或非表头分别进行处理*/
		*L = (*L)->next;
	}
	else
	{
		ap->next = p->next;
	}
	free(p);
	return 1;
}

void test(node** L){
	//node* L只能改变L中的内容，node** L才能改变L的指向
	//node* L，L指向的是node的内容，node** L，L指向的是保存node*指针的地址
	//使用node* L的时候，L重新赋值只是会将L指向的内容由一个node改为其他node，但是这只是改变了局部变量
	printf("3%x\n", L); //L是一个地址
	node *a = (node*)calloc(1, sizeof(node));
	a->next = *L;
	a->data = 2;
	*L = a;
	printf("4%x\n", L);
}

int main(){
	LinkList L = NULL;
	//initList(L);
	insertFirstList(&L, 10);
	insertLastList(&L, 35);
	int status = insertPosList(&L, 2, 23);
	insertOrderList(&L, 100);
	deleteValueList(&L, 23);
	printf("====%d\n", getElem(L, 1));
	printf("====%d\n", getElem(L, 2));
	printf("====%d\n", getElem(L, 3));

	//clearList(L);
	getchar();
	return 0;
}