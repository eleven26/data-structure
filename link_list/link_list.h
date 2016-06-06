#include "common.h"

typedef int ElemType;

struct node
{
	ElemType data;
	struct node * next;
};

typedef node* LinkList;

/*��ʼ����������������ı�ͷָ����Ϊ��*/
void initList(LinkList *L);

/*��������е�����Ԫ�أ��ͷ����н�㣬ʹ֮��Ϊһ���ձ�*/
void clearList(LinkList *L);

/*���ص�����ĳ���*/
int sizeList(LinkList *L);

/*��鵥�����Ƿ�Ϊ�գ����򷵻�1�����򷵻�0*/
int emptyList(LinkList *L);

/*���������е�pos������Ԫ��*/
ElemType getElem(LinkList L, int pos);

/*����һ��������*/
void traverseList(LinkList *L);

/*�ӵ������в���ֵΪe�ĵ�һ��Ԫ�أ����ҵ��򷵻ص�ַ*/
ElemType* findList(LinkList *L, ElemType e);

/*�ѵ�������posλ�õ�ֵ�޸�Ϊe���ɹ�����1�����򷵻�0*/
int updateList(LinkList *L, int pos, ElemType e);

/*�������ͷ����һ��Ԫ��*/
void insertFirstList(LinkList *L, ElemType e);

/*�������ĩβ���һ��Ԫ��*/
void insertLastList(LinkList *L, ElemType e);

/*�������е�pos�����λ�ò���Ԫ��Ϊx�Ľڵ㣬������ɹ�����1�����򷵻�0*/
int insertPosList(LinkList *L, int pos, ElemType e);

/*�����������в���Ԫ��e��㣬ʹ�ò������Ȼ����*/
void insertOrderList(LinkList *L, ElemType e);

/*�ӵ�������ɾ����ͷ��㣬���Ѹý���ֵ���أ���ɾ��ʧ��ֹͣ����*/
ElemType deleteFirstList(LinkList *L);

/*�ӵ�������ɾ����β��㲢��������ֵ��ɾ��ʧ�����˳�*/
ElemType deleteLastList(LinkList *L);

/*�ӵ�����ɾ����pos����㲢��������ֵ��ɾ��ʧ���˳�*/
ElemType deletePosList(LinkList *L, int pos);

/*�ӵ�������ɾ��ֵΪe�ĵ�һ���ڵ㣬�ɹ�����1��ʧ�ܷ���-1*/
int deleteValueList(LinkList *L, ElemType e);