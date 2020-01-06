//
//  link_ilst.c
//  
//
//  Created by baiguiren on 8/24/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node * next;
}node;

typedef struct LinkList{
    node *head;
    node *end;
}list;

/*初始化链表，即将单链表的表头指针设为空*/
void initList(list *L){
    L->head = 0;
}

/*清除链表中的所有元素，释放所有结点，使之成为一个空表*/
void clearList(list *L){
    node *head, *next;
    head = L->head;
    while (head) {
        next = head->next;
        free(head);
        head = next;
    }
}

/*返回单链表的长度*/
int sizeList(list *L){
    node *p = L->head;
    int length = 0;
    while (p) {
        length ++;
        p = p->next;
    }
    return length;
}

/*检查单链表是否为空，空则返回1，否则返回0*/
int emptyList(list *L){
    return !L;
}

/*返回链表中第pos个结点的元素*/
ElemType getElem(list L, int pos){
    ElemType e;
    node *p;
    int cur = 0;
    p = L.head;
    while (p && cur < pos) {
        p = p->next;
        cur ++;
    }
    if (cur == pos){
        e = p->data;
    }else{
        printf("位置非法!\n");
        exit(-1);
    }
    
    return e;
}

/*遍历一个单链表*/
void traverseList(list *L){
    node *p = L->head;
    while (p) {
        printf("%d,", p->data);
        p = p->next;
    }
    printf("\n");
}

/*从单链表中查找值为e的第一个元素，查找到则返回地址*/
int findList(list *L, ElemType e){
    node *p = L->head;
    int cur = 0;
    while (p) {
        if (e == p->data) {
            return cur;
        }
        p = p->next;
        cur ++;
    }
    return -1;
}

/*把单链表中pos位置的值修改为e，成功返回1，否则返回0*/
int updateList(list *L, int pos, ElemType e){
    node *p = L->head;
    int cur = 0;
    while (p && cur < pos) {
        p = p->next;
        cur ++;
    }
    if (cur == pos) {
        p->data = e;
        return 1;
    }
    return 0;
}

/*向单链表表头插入一个元素*/
void insertFirstList(list *L, ElemType e){
    node *n = malloc(sizeof(node));
    node *temp;
    n->data = e;
    temp = L->head;
    L->head = n;
    n->next = temp;
}

/*向单链表的末尾添加一个元素*/
void insertLastList(list *L, ElemType e){
    node *p = L->head;
    while (p) {
        if (!p->next){
            node *n = malloc(sizeof(node));
            n->data = e;
            n->next = 0;
            p->next = n;
            return ;
        }
        p = p->next;
    }
}

/*向单链表中第pos个结点位置插入元素为x的节点，若插入成功返回1，否则返回0*/
int insertPosList(list *L, int pos, ElemType e){
    node *p = L->head, *prev;
    int cur = 0;
    while (p && cur < pos) {
        if (cur+1 == pos){
            prev = p;
        }
        p = p->next;
        cur ++;
    }
    if (cur == pos) {
        node *n = malloc(sizeof(node));
        n->data = e;
        prev->next = n;
        n->next = p;
        return 1;
    }
    return 0;
}

void check_null(node *pointer){
    if (!pointer){
        printf("内存分配失败!\n");
        exit(1);
    }
    return ;
}

/*向有序链表中插入元素e结点，使得插入后仍然有序, 如小到大*/
void insertOrderList(list *L, ElemType e){
    node *p = L->head;
    while (p) {
        if (p->data <= e && p->next && p->next->data >= e) {
            node *n = malloc(sizeof(node)), *temp;
            check_null(n);
            temp = p->next;
            n->data = e;
            p->next = n;
            n->next = temp;
            return ;
        }
        p = p->next;
    }
}

/*从单链表中删除表头结点，并把该结点的值返回，若删除失败停止运行*/
ElemType deleteFirstList(list *L){
    node *head = L->head;
    if (head){
        ElemType e;
        e = head->data;
        L->head = L->head->next;
        return e;
    }else{
        printf("链表为空!\n");
        exit(1);
    }
    return -1;
}

/*从单链表中删除表尾结点并返回它的值，删除失败则退出*/
ElemType deleteLastList(list *L){
    node *p = L->head, *prev;
    while (p) {
        if (!p->next){
            ElemType e = p->data;
            prev->next = 0; //这里不能用p=0; p=0只是改变指针p本身，而不能改变p指向的内容
            return e;
        }
        prev = p;
        p = p->next;
    }
    printf("删除失败!\n");
    exit(-1);
}

/*从单链表删除第pos个结点并返回它的值，删除失败退出*/
ElemType deletePosList(list *L, int pos){
    node *p = L->head, *prev;
    int cur = 0;
    while (p && cur < pos) {
        prev = p;
        p = p->next;
        cur ++;
    }
    if (cur == pos){
        ElemType e = p->data;
        prev->next = p->next;
        return e;
    }
    printf("删除失败!\n");
    exit(-1);
}

/*从单链表中删除值为e的第一个节点，成功返回1，失败返回-1*/
int deleteValueList(list *L, ElemType e){
    node *p = L->head, *prev = L->head;
    while (p) {
        if (p->data == e){
            prev->next = p->next;
            free(p);
            return 1;
        }
        prev = p;
        p = p->next;
    }
    return -1;
}



int main(){
    list L;
    initList(&L);
    insertFirstList(&L, 12);
    insertFirstList(&L, 13);
    insertFirstList(&L, 14);
    printf("链表长度:%d\n", sizeList(&L));
    printf("%d\n", getElem(L, 1));
    traverseList(&L);
    printf("链表是否为空: %s\n", emptyList(&L) ? "是":"否");
    printf("元素12的位置: %d\n", findList(&L, 12));
    updateList(&L, 2, 15);
    traverseList(&L);
    
    insertLastList(&L, 89);
    traverseList(&L);
    
    insertPosList(&L, 3, 56);
    traverseList(&L);
    
    insertOrderList(&L, 57);
    traverseList(&L);
    printf("链表长度:%d\n", sizeList(&L));
    
    deleteFirstList(&L);
    traverseList(&L);
    
    printf("deleted: %d\n", deleteLastList(&L));
    traverseList(&L);
    
    printf("deleted: %d\n", deletePosList(&L, 1));
    traverseList(&L);
    
    deleteValueList(&L, 56);
    traverseList(&L);
    
    clearList(&L);
    return 0;
}


