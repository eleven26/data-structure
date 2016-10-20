#include<stdio.h>
#include<stdlib.h>

#define INIT_SIZE 100
typedef int elem_type;
const elem_type initialize_value;
typedef struct{
	elem_type data;
	struct node *next;
}node;

void println(char *string){
	printf("%s\n", string);
}

//��INIT_SIZEΪ��С��ʼ�����Ա�
void init_list(node **L, int size){
	node *begin_address = calloc(size, sizeof(node));
	if (!begin_address){
		println("���Ա��ʼ��ʧ�ܣ�");
		exit(1);
	}
	*L = begin_address;
}

//�ݻ����Ա�
int destroy_list(node **L) {
	if (*L)
	{
		free(*L);
		return 0;
	} else {
		return -1; 
	}
}

//������Ա������ٲ�ͬ����յ�ʱ�򳤶Ȼ���ԭ���ĳ��ȣ�ֻ��ԭ��������û��
int clear_list(node **list_address){
	node *p = *list_address;
	while (p){
		p->data = initialize_value;
		printf("initialize_value=%d\n", initialize_value);
		p = p->next;
	}
	return 0;
}

int main(){
	node *L;
	init_list(&L, INIT_SIZE);
	L[10].data = 20;
	clear_list(&L);
	printf("L[10].data= %d\n", L[10].data);
	if (destroy_list(&L) == 0){
		println("�������Ա�ɹ�");
	}
	else{
		println("�������Ա�ʧ�ܣ�");
	}
	return 0;
}