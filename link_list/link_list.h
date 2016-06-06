#include "common.h"

typedef int ElemType;

struct node
{
	ElemType data;
	struct node * next;
};

typedef node* LinkList;

/*初始化链表，即将单链表的表头指针设为空*/
void initList(LinkList *L);

/*清除链表中的所有元素，释放所有结点，使之成为一个空表*/
void clearList(LinkList *L);

/*返回单链表的长度*/
int sizeList(LinkList *L);

/*检查单链表是否为空，空则返回1，否则返回0*/
int emptyList(LinkList *L);

/*返回链表中第pos个结点的元素*/
ElemType getElem(LinkList L, int pos);

/*遍历一个单链表*/
void traverseList(LinkList *L);

/*从单链表中查找值为e的第一个元素，查找到则返回地址*/
ElemType* findList(LinkList *L, ElemType e);

/*把单链表中pos位置的值修改为e，成功返回1，否则返回0*/
int updateList(LinkList *L, int pos, ElemType e);

/*向单链表表头插入一个元素*/
void insertFirstList(LinkList *L, ElemType e);

/*向单链表的末尾添加一个元素*/
void insertLastList(LinkList *L, ElemType e);

/*向单链表中第pos个结点位置插入元素为x的节点，若插入成功返回1，否则返回0*/
int insertPosList(LinkList *L, int pos, ElemType e);

/*向有序链表中插入元素e结点，使得插入后仍然有序*/
void insertOrderList(LinkList *L, ElemType e);

/*从单链表中删除表头结点，并把该结点的值返回，若删除失败停止运行*/
ElemType deleteFirstList(LinkList *L);

/*从单链表中删除表尾结点并返回它的值，删除失败则退出*/
ElemType deleteLastList(LinkList *L);

/*从单链表删除第pos个结点并返回它的值，删除失败退出*/
ElemType deletePosList(LinkList *L, int pos);

/*从单链表中删除值为e的第一个节点，成功返回1，失败返回-1*/
int deleteValueList(LinkList *L, ElemType e);