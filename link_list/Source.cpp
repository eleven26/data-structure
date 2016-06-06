#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "link_list.h"

void initList(LinkList *L){
	/*��ʼ����������������ı�ͷָ����Ϊ��*/
	*L = NULL;
	return;
}

void clearList(LinkList *L){
	/*��������е�����Ԫ�أ��ͷ����н�㣬ʹ֮��Ϊһ���ձ�*/
	node *cur_node, *next_node;
	cur_node = *L;
	/*���������������ͷ�ÿ�����*/
	while (cur_node!=NULL)
	{
		next_node = cur_node->next; /*������һ������ָ��*/
		free(cur_node);
		cur_node = next_node;
	}
	*L = NULL;
	return;
}

int sizeList(LinkList *L){
	/*���ص�����ĳ���*/
	int count = 0;
	while (*L!= NULL)
	{
		count++;
		*L = (*L)->next;
	}
	return count;
}

int emptyList(LinkList *L){
	/*��鵥�����Ƿ�Ϊ�գ����򷵻�1�����򷵻�0*/
	return *L == NULL ? 1 : 0;
}

ElemType getElem(LinkList L, int pos){
	/*���������е�pos������Ԫ��*/
	int i = 0;
	if (pos < 1){
		printf("λ�÷Ƿ�!");
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
		printf("λ�÷Ƿ�!");
	}
	return -1;
}

void traverseList(LinkList *L){
	/*����һ��������*/
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
	/*�ӵ������в���ֵΪe�ĵ�һ��Ԫ�أ����ҵ��򷵻ص�ַ*/
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
	/*�ѵ�������posλ�õ�ֵ�޸�Ϊe���ɹ�����1�����򷵻�0*/
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
	//node* L��node **L��node* L��ʱ��L��һ��node��㣬��node **L��ʱ��L��һ��ָ��node�ĵ�ַ
	//node* Node��ʾNode��ָ��node���ĵ�ַ
	/*�������ͷ����һ��Ԫ��*/
	node* new_node;
	new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("�ڴ����ʧ��");
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
	/*�������ĩβ���һ��Ԫ��*/
	node* new_node;
	new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("�ڴ����ʧ��!\n");
		exit(1);
	}
	/*��e�����½ڵ��data�򣬰ѿ�ֵ��ֵ���½ڵ��next*/
	new_node->data = e;
	new_node->next = NULL;
	/*��ԭ��Ϊ�ձ�����Ϊ��ͷ����*/
	if (*L == NULL){
		*L = new_node;
	}
	else
	{
		/*�ҵ�β�ڵ㲢��ɲ���*/
		node* p = *L;
		while (p->next != NULL){
			p = p->next;
		}
		p->next = new_node;
	}
	return;
}

int insertPosList(LinkList *L, int pos, ElemType e){
	/*�������е�pos�����λ�ò���Ԫ��Ϊx�Ľڵ㣬������ɹ�����1�����򷵻�-1*/
	int i = 0;
	node * p = *L,*ap = NULL;
	node * new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("�ڴ����ʧ��!\n");
		return -1;
	}
	/*��pos�Ƿ��Ľ��д���*/
	if (pos <= 0){
		printf("posλ�÷Ƿ�!\n");
		return -1;
	}
	/*���ҵ�pos�����*/
	while (p!=NULL)
	{
		i++;
		if (pos == i){
			break;
		}
		ap = p; //��ǰָ��
		p = p->next; //��һ��ָ��
	}
	if (pos == i){
		//��p�滻Ϊnew_node
		new_node->data = e;
		new_node->next = p;
		if (ap == NULL){//�����ͷ
			p = new_node;
		}
		else{
			ap->next = new_node;
		}
		return 0;
	}
	else{
		printf("λ�ó���������!\n");
		return -1;
	}
}

void insertOrderList(LinkList *L, ElemType e){
	/*�����������в���Ԫ��e��㣬ʹ�ò������Ȼ����*/
	node *p = *L, *ap = NULL;
	node *new_node = (node*)calloc(1, sizeof(node));
	if (new_node == NULL){
		printf("�ڴ����ʧ��!\n");
		exit(1);
	}
	new_node->data = e;
	/*�������û��Ԫ��*/
	if (p == NULL || e < p->data){
		new_node->next = p;
		p = new_node;
		return;
	}
	/*˳����ҳ�e���Ĳ���λ��*/
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
	/*�ӵ�������ɾ����ͷ��㣬���Ѹý���ֵ���أ���ɾ��ʧ��ֹͣ����*/
	ElemType temp;
	node *p = *L;
	if (p == NULL){
		printf("����Ϊ��!\n");
		exit(1);
	}
	temp = p->data;
	*L = (*L)->next;
	free(p); /*���ձ�ɾ���ı�ͷ���*/
	return temp;
}

ElemType deleteLastList(LinkList *L){
	/*�ӵ�������ɾ����β��㲢��������ֵ��ɾ��ʧ�����˳�*/
	ElemType temp;
	node *p = *L, *ap = NULL;
	if (p == NULL){
		printf("������Ϊ��!\n");
		exit(1);
	}
	while (p->next != NULL)
	{
		ap = p;
		p = p->next;
	}
	if (ap == NULL){
		/*ֻ��һ�����*/
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
	/*�ӵ�����ɾ����pos����㲢��������ֵ��ɾ��ʧ���˳�*/
	int i = 0;
	ElemType temp;
	node *p = *L, *ap = NULL;
	if ((p == NULL) || (pos <= 0)){
		printf("����Ϊ�ջ���pos����ȷ!\n");
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
		printf("pos����ȷ!\n");
		exit(1);
	}
	if (pos == 1){
		/*pos==1��ʱ��*/
		temp = p->data;
		*L = (*L)->next;
		free(p);
		return temp;
	}
	else
	{
		ap->next = p->next;
		temp = p->data;
		free(p); /*�ͷű�ɾ�������ڴ�*/
		return temp;
	}
}

int deleteValueList(LinkList *L, ElemType e){
	/*�ӵ�������ɾ��ֵΪe�ĵ�һ���ڵ㣬�ɹ�����1��ʧ�ܷ���-1*/
	node *p = *L, *ap = NULL;
	/*�ӵ������в���ֵΪe�Ľ��*/
	while (p!=NULL)
	{
		if (p->data == e){
			break;
		}
		ap = p;
		p = p->next;
	}
	if (p == NULL){
		/*������ʧ�ܣ��򷵻�-1*/
		return -1;
	}
	if (ap == NULL){
		/*���ɾ�����Ǳ�ͷ��Ǳ�ͷ�ֱ���д���*/
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
	//node* Lֻ�ܸı�L�е����ݣ�node** L���ܸı�L��ָ��
	//node* L��Lָ�����node�����ݣ�node** L��Lָ����Ǳ���node*ָ��ĵ�ַ
	//ʹ��node* L��ʱ��L���¸�ֵֻ�ǻὫLָ���������һ��node��Ϊ����node��������ֻ�Ǹı��˾ֲ�����
	printf("3%x\n", L); //L��һ����ַ
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