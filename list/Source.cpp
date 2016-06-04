#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "list.h"

void reMalloc(struct SeqList *L, int newSize){
	//���·������Ա��ڴ棬��СΪnewSize
	node *new_List =(node *) calloc(L->maxSize , sizeof(node));  //������ʱ�ڴ��
	memcpy(new_List, L->list, L->maxSize * sizeof(node));  //����ĳ���Ӧ����L->maxSize * sizeof(node)��������L->maxSize
	free(L->list);
	L->list = NULL;

	int tmp_size = L->maxSize;
	L->list = (node *) calloc(newSize , sizeof(node)); //�����µ��ڴ�
	memcpy(L->list, new_List, L->maxSize * sizeof(node));
	L->maxSize = newSize;
	free(new_List);
	new_List = NULL;

	for (int i = tmp_size; i < L->maxSize; i++)
	{
		L->list[i].is_used = 0; //ÿ��Ԫ�ض���־Ϊδʹ��
	}
}//reMalloc

Status InitList(struct SeqList *L, int maxSize){
	//����һ���յ����Ա�
	if (maxSize < 0){
		printf("maxSize����!");
		exit(1);
	}
	L->list = (node*) calloc(maxSize, sizeof(node));
	for (int i = 0; i < maxSize; i++)
	{
		L->list[i].is_used = 0; //ÿ��Ԫ�ض���־Ϊδʹ��
	}
	L->size = 0;
	L->maxSize = maxSize;
	return OK;
}//InitList

Status DestroyList(struct SeqList *L){
	//�����б�
	free(L->list);
	L->size = 0;
	L->maxSize = 0;
	L->list = NULL;
	return OK;
}//DestroyList

Status ClearList(struct SeqList *L){
	//��L����Ϊ�ձ����L�е�����Ԫ�أ��ͷŴ洢�ձ�
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
	//��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
	return L->size == 0 ? TRUE : FALSE;
}//ListEmpty

int ListLength(struct SeqList *L){
	//���ص�ǰ���Ա�ĳ���
	return L->maxSize;
}//ListLength

ElemType GetElem(struct SeqList *L, int pos){
	//�������Ա���λ��pos��Ԫ��
	if (pos<1 || pos>L->maxSize){
		printf("Ԫ�����Խ��");
		return OVERLOW;
	}
	if (L->list[pos - 1].is_used = 0){
		printf("��λ��û��Ԫ�أ�");
		return ERROR;
	}
	return L->list[pos - 1].value;
}//GetElem

void MoveList(struct SeqList *L, int pos){
	//�����Ա�L��posλ�ÿ�ʼ�����
	for (int i = L->maxSize - 1; i > pos; i--)
	{	/*i>pos������i>=pos������L->list[pos].is_used = 1
		//��i=pos+1ʱ�����list[pos]����ƶ�һλ������list[pos]�Ϳ���������Ԫ����
		//�����ȡi=pos�Ļ�����ʹ��L->list[pos].is_used���1���Ͳ��ܲ�����Ԫ����
		*/
		//����±���L->maxSize - 1
		//ÿ��Ԫ�غ��ƣ������һ��Ԫ�ؿ�ʼ�ƶ�����ÿ�������ƶ���Ԫ�ض��ƶ�
		if (L->list[i].is_used == 0 && L->list[i - 1].is_used == 1){
			//�������ʹ�õĻ��ᱻ����
			L->list[i].value = L->list[i - 1].value;
			L->list[i].is_used = L->list[i - 1].is_used;
			L->list[i - 1].is_used = 0; //i-1λ�õ�Ԫ���Ѿ��ƶ���iλ��
		}
	}
}//MoveList

Status PutElem(struct SeqList *L, int pos, ElemType e){
	//��λ��pos����Ԫ��e��λ��pos֮��Ҫ���ƣ�1<= pos <= L-maxSize
	pos = pos - 1;
	if (pos<0 || pos>L->maxSize - 1){
		printf("�Ƿ�λ�ò���\n");
		return OVERLOW;
	}
	if (L->size == L->maxSize){
		printf("���Ա��Ѿ��������ɸ���Ԫ��");
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
				printf("���Ա��λ��%d�޷�����\n", pos);
				return OVERLOW;
			}
		}
		return OK;
	}
}//PutElem

Status UpdatePosElem(struct SeqList *L, int pos, ElemType e){
	//ֱ���滻���Ա�λ��pos��Ԫ�أ������ı�����Ԫ�ص�λ��
	L->list[pos - 1].value = e;
	L->list[pos - 1].is_used = 1;
	return OK;
}//UpdatePosElem

void InsertFirstList(struct SeqList *L, ElemType e){
	//�����Ա�L�ı�ͷ����Ԫ��e
	if (L->list[L->maxSize - 1].is_used == 1){
		reMalloc(L, L->maxSize + 1);
	}
	MoveList(L, 0);
	L->list[0].value = e;
	L->list[0].is_used = 1;
}//InsertFirstList

void InsertLastList(struct SeqList *L, ElemType e){
	//�����Ա�L�ı�β����Ԫ��e
	if (L->list[L->maxSize - 1].is_used == 1){
		reMalloc(L, L->maxSize + 1);
	}
	L->list[L->maxSize - 1].value = e;
	L->list[L->maxSize - 1].is_used = 1;
}//InsertLastList

ElemType deleteElem(struct SeqList *L, int pos){
	//ɾ��λ��pos��Ԫ��
	if (L->size == 0){
		printf("���Ա�Ϊ��!\n");
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
		printf("��λ��û��Ԫ��\n");
		return ERROR;
	}
	
}//deleteElem

ElemType deleteFirstList(struct SeqList *L){
	//�����Ա�L��ɾ����ͷԪ�ز�����������ɾ��ʧ�ܷ��ش������
	return deleteElem(L, 0);
}//deleteFirstList

ElemType deleteLastList(struct SeqList *L){
	//�����Ա�L��ɾ����βԪ�ز�����������ɾ��ʧ�ܷ��ش������
	int pos = L->maxSize - 1;
	return deleteElem(L, pos);
}//deleteLastList

ElemType deletePosList(struct SeqList *L, int pos){
	//�����Ա�L��ɾ��λ��pos��Ԫ��
	pos = pos - 1;
	return deleteElem(L, pos);
}//deletePosList

Status visit(ElemType e){
	return e > 10 ? TRUE : FALSE;
}

void traverseList(struct SeqList *L){
	//��ͨ��������ӡ���Ա�洢��ֵ��Ԫ��
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
	//���ζ�L��ÿ������Ԫ�ص��ú���visit��һ��visit()ʧ�ܣ������ʧ�ܡ�
	for (int i = 0; i < L->maxSize; i++){
		if (L->list[i].is_used == 1 && visit(L->list[i].value)){
			return FALSE;
		}
	}
	return TRUE;
}//ListTraverse

int FindList(struct SeqList *L, ElemType e){
	//�����Ա��в���ֵ��e��ȵ�Ԫ�أ������ҳɹ�������λ�ã����򷵻�-1
	//������ظ�Ԫ��ֻ�Ƿ��ص�һ�����ֵ�λ��
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
	//����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��
	//��������Ԫ�ز����ڣ��򷵻�-1
	for (int i = 0; i < L->maxSize; i++){
		if (L->list[i].is_used == 1 && compare(e, L->list[i].value)){
			return i;
		}
	}
	return -1;
}//LocateElem

ElemType PriorElem(struct SeqList *L, int pos){
	//��pos������Ԫ�أ��Ҳ��ǵ�һ�����򷵻�����ǰ�����������ʧ��
	if (L->size>1 && pos != 0){
		if (L->list[pos - 1].is_used == 1){
			return L->list[pos - 1].value;
		}
		else
		{
			printf("��Ԫ��ǰ��Ԫ��Ϊ��!\n");
			return 0;
		}
	}
	return ERROR;
}//PriorElem

ElemType NextElem(struct SeqList *L, int pos){
	//��pos������Ԫ�أ��Ҳ������һ�����򷵻����ĺ�̣��������ʧ��
	if (L->size>1 && pos < L->maxSize-1){
		if (L->list[pos + 1].is_used == 1){
			return L->list[pos + 1].value;
		}
		else
		{
			printf("��Ԫ�غ��Ԫ��Ϊ��!\n");
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

	printf("10��λ��:%d\n", FindList(&L, 10));

	traverseList(&L);
	
	printf("new size:%d\n",J->maxSize);
	//traverseList(&L);
	printf("maxSize:%d\n", J->size);
	printf("�������:%d\n", ListTraverse(&L,visit));

	printf("����21�ĵ�һ��Ԫ��λ�� %d\n", LocateElem(&L, 21, compare));

	printf("λ��11��ǰ��Ԫ��Ϊ:%d\n", PriorElem(&L, 1));

	printf("sizeof(L)=%d\n", sizeof(L)); 
	//Lʼ�յ���4��ԭ���ǣ���L��Ϊ�������ݵ�ʱ��"�˻�"Ϊָ�룬sizeofֻ�ܵõ�ָ���Ӧ���͵ĳ���.
	
	
	
	getchar();
	return 0;
}