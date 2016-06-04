#include "common.h"

typedef int ElemType;
struct node{
	ElemType value; //Ԫ�ص�ֵ
	int is_used; //1��ʾ����ʹ�ã�0��ʾ����
};

typedef node* List;

struct SeqList
{
	node *list;
	int size;  //��¼��ǰ����
	int maxSize; //��¼�������ɵĳ���
};

void reMalloc(struct SeqList *L, int newSize);
//���·������Ա��ڴ�

Status InitList(struct SeqList *L, int MaxSize);
//����һ���յ����Ա�

Status Destroy(struct SeqList *L);
//�������Ա�L

Status ClearList(struct SeqList *L);
//��L����Ϊ�ձ�

Status ListEmpty(struct SeqList *L);
//��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE

int ListLength(struct SeqList *L);
//����L��Ԫ�صĸ���

ElemType GetElem(struct SeqList *L, int pos);
//��e����L�е�i������Ԫ�ص�ֵ

Status PutElem(struct SeqList *L, int pos, ElemType e);
//��λ��i����Ԫ��e

Status ListTraverse(struct SeqList *L, Status(*visit));
//���ζ�L��ÿ������Ԫ�ص��ú���visit��һ��visit()ʧ�ܣ������ʧ�ܡ�

int FindList(struct SeqList *L, ElemType e);
//�����Ա��в���ֵ��e��ȵ�Ԫ�أ������ҳɹ�������λ�ã����򷵻�-1

Status UpdatePosElem(struct SeqList *L, int pos, ElemType e);
//ֱ���滻���Ա�λ��pos��Ԫ�أ������ı�����Ԫ�ص�λ��

void InsertFirstList(struct SeqList *L, ElemType e);
//�����Ա�L�ı�ͷ����Ԫ��e

void InsertLastList(struct SeqList *L, ElemType e);
//�����Ա�L�ı�β����Ԫ��e

ElemType deleteElem(struct SeqList *L, int pos);
//ɾ��λ��pos��Ԫ��

ElemType deleteFirstList(struct SeqList *L);
//�����Ա�L��ɾ����ͷԪ�ز�����������ɾ��ʧ�ܷ��ش������

ElemType deleteLastList(struct SeqList *L);
//�����Ա�L��ɾ����βԪ�ز�����������ɾ��ʧ�ܷ��ش������

ElemType deletePosList(struct SeqList *L, int pos);
//�����Ա�L��ɾ��λ��pos��Ԫ��

//==========================================================

Status LocateElem(List L, ElemType e, Status(*compare));
//����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��
//��������Ԫ�ز����ڣ��򷵻�0

Status PriorElem(List L, ElemType cur_e, ElemType &pre_e);
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ��

Status NextElem(List L, ElemType cur_e, ElemType &next_e);
//��cur_e��L������Ԫ�أ��Ҳ������һ��������next_e��������ǰ�����������ʧ��

Status ListInsert(List &L, int i, ElemType e);
//��L�еĵ�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ���+1

Status ListDelete(List &L, int i, ElemType &e);
//ɾ���̵ĵڣ������Ԫ�أ������ã巵����ֵ���̵ĳ��ȣ���
