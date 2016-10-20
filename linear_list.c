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

//以INIT_SIZE为大小初始化线性表
void init_list(node **L, int size){
	node *begin_address = calloc(size, sizeof(node));
	if (!begin_address){
		println("线性表初始化失败！");
		exit(1);
	}
	*L = begin_address;
}

//摧毁线性表
int destroy_list(node **L) {
	if (*L)
	{
		free(*L);
		return 0;
	} else {
		return -1; 
	}
}

//清空线性表，和销毁不同，清空的时候长度还是原来的长度，只是原来的数据没了
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
		println("销毁线性表成功");
	}
	else{
		println("销毁线性表失败！");
	}
	return 0;
}