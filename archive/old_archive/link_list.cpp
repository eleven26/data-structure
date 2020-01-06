#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Elemtype;
typedef int Status;

#define OK 1
#define SUCCESS 1
#define ERROR  -1

typedef struct node{
	Elemtype data;
	struct node *next;
}*LinkList;

Status init_link_list(LinkList *L){
	*L = NULL;
	return 0;
}

Status insert_first(LinkList *L, Elemtype e){
	struct node *new_node = (node*)calloc(1, sizeof(node));
	if(!new_node){
		printf("memory allocation failed!\n");
		return -1; 
	}
	new_node->data = e;
	new_node->next = *L;
	//(*L)->next = new_node;
	*L = new_node;
	//*L是一个指向链表的指针
	return 0;
}

Status insert_pos(LinkList *L,int pos, Elemtype e){
	struct node *new_node = (node*)calloc(1, sizeof(node));
	if(!new_node){
		printf("memory allocation failed!\n");
		return -1; 
	}
	int j=1;
	node *p = *L; //如果直接用*L会改变原链表，而*p只是指针变量,*L是指向链表开头的地址
	//而我们需要做的是对链表内部结构进行更改，而不是链表起始位置
	new_node->data = e;
	while(p && j<pos-1){
		j++;
		p = p->next;
	}
	if(!p||j>pos){
		printf("position illegal!\n");
		return -1;
	}
	new_node->next = p->next;
	p->next = new_node;
	return SUCCESS;
}

Status list_delete(LinkList *L, int pos, Elemtype *e){
	if(pos<1){
		printf("position illegal!\n");
		return ERROR;
	}
	int j=1;
	node *p = *L;
	while(p && j<pos-1){
		j++;
		p = p->next;
	}

	if(!(p->next)){
		printf("position illegal!\n");
		return ERROR;
	}
	//删除p->next结点
	*e = p->data;
	//p = p->next;
//	free(p);
	node* q = p->next;
	p->next = q->next;
	free(q);
	q = NULL;
	return SUCCESS;
}

int list_length(LinkList L){
	int length = 0;
	while(L){
		++length;
		L = L->next;
	}
	//while(L && ++length && (L=L->next)){}
	return length;
}

Status get_elem(LinkList L, int pos, Elemtype *e){
	if(pos<1) return -1;
	int j=1;
	while(L && j<pos){
		j++;
		L = L->next;
	}
	if(!L) return -1;
	*e = L->data;
	return 1;
}

void merge_list(LinkList *La, LinkList *Lb, LinkList *Lc){
	//已知单链线性表La和Lb的元素按值非递减排列
	//归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
	node* pa = (*La)->next; //指向La第一个元素
	node* pb = (*Lb)->next; //指向Lb第一个元素
	node* pc;
	*Lc = pc = *La; //pc是Lc尾指针

	while(pa && pb){
		if(pa->data <= pb->data){
			//pa->data插入Lc
			pc->next = pa;
			pc = pa;
			pa = pa->next; //pa插入后，指向下一个元素
		}else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa: pb;
	free(*Lb);
}

void test(LinkList *L){
	node* p = (node*)calloc(1, sizeof(node));
	for(int i=5;i>0;i--){
		insert_first(L, i);
	}
}

void test1(LinkList *L){
	node* p = (node*)calloc(1, sizeof(node));
	insert_first(L, 15);
	insert_first(L, 13);
	insert_first(L, 10);
	insert_first(L, 7);
	insert_first(L, 6);
}
void traverse_list(LinkList L){
	int length = list_length(L);
	for(int i=0;i<length;i++){
		Elemtype e=0;
		get_elem(L, i, &e);
		printf("L[%d]=%d\n", i, e);
	}
}

/**
 * 需要对变量结构进行改变的时候才传指针
 */
int main(){
	LinkList L=NULL;
	//&L是一个指向*node的指针，*node是取指向node的指针的值，两者不同

	LinkList la=0,lb=0,lc=0;
	test(&la);
	traverse_list(la);
	printf("---------\n");
	test1(&lb);
	traverse_list(lb);
	printf("---------\n");
	merge_list(&la,&lb,&lc);
	traverse_list(lc);
	return 0;
}
