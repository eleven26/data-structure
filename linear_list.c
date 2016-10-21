#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_SIZE 100
#define DEBUG 1
typedef int elem_type;

typedef struct list{
    elem_type* elements;
    int size;
}list;

/**
 * initialize linear list
 * @param L
 */
int init_list(list *L) {
    L->size = INIT_SIZE;
    size_t list_size = L->size * sizeof(elem_type);
    //L->elements = (elem_type*)calloc((size_t)L->size, sizeof(elem_type));
    //elem_type *new_list_address = (elem_type*)calloc((size_t)(L->size), sizeof(elem_type));
    L->elements = (elem_type*)calloc((size_t)(L->size), sizeof(elem_type));
    if (!L->elements){
        printf("初始化线性表内存分配失败!\n");
        exit(1);
    }
    //memcpy(L->elements, new_list_address, list_size);
    /*
    L->elements = new_list_address;
    if (memcmp(L->elements, new_list_address, list_size) != 0){
        //如果内存复制失败,表示未能完成初始化
        printf("初始化线性表失败!\n");
        exit(2);
    }
     */
    if (DEBUG){
        printf("初始化线性表成功!\n");
    }
    return 0;
}

/**
 * destroy linear list
 * @param l
 */
void destroy_list(list *L){
    free(L->elements);
    //free之后, 指针还是会指向原来的地址, 变成了野指针, 需要p=NULL
    L->elements = NULL;
    if (L->elements != 0){
        printf("销毁线性表失败!\n");
        exit(3);
    } else if (DEBUG) {
        printf("销毁线性表成功\n");
    }
}

int main(int argc, char **argv){
    list L;
    if (init_list(&L) != 0){
        //初始化失败
        exit(3);
    }
    destroy_list(&L);
}