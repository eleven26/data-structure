#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define INIT_SIZE 100
#define DEBUG true
//typedef int elem_type;

typedef int data_type;
 //添加标志位, 标志该位置是否已经有元素

typedef struct{
    data_type data;
    int is_used;
}elem_type;

typedef struct{
    elem_type* elements;
    int size;
    int max_size;
}list;

/**
 * initialize linear list
 * @param L
 */
void init_list(list *List) {
    List->size = INIT_SIZE;
    List->elements = (elem_type*)calloc((size_t)(List->size), sizeof(elem_type));
    if (!List->elements){
        printf("初始化线性表内存分配失败!\n");
        exit(1);
    }
    if (DEBUG){
        printf("初始化线性表成功!\n");
    }
}

/**
 * destroy linear list
 * @param L
 */
void destroy_list(list *List){
    free(List->elements);
    //free之后, 指针还是会指向原来的地址, 变成了野指针, 需要p=NULL
    List->elements = NULL;
}

int list_empty(list List){
    return List.size == 0 ? true : false;
}

int list_length(list List) {
    return List.size;
}

elem_type* realloc_size(elem_type *source, size_t old_size, size_t new_size){
    elem_type *new_list_address = (elem_type*) calloc(new_size, sizeof(elem_type));
    if (!new_list_address) {
        printf("重新分配内存失败!\n");
        exit(1);
    } else {
        memcpy(new_list_address, source, old_size);
    }
    return new_list_address;
}

//在位置location处插入元素element, location从0算起
void list_insert_loc(list *List, int location, data_type data) {
    if (location + 1 > List->size) {
        //插入的位置大于列表size, 重新分配内存
        int new_size = ((int)(location / List->size) + 1) * List->size;
        List->elements = realloc_size(List->elements, (size_t)List->size, (size_t)new_size);
    }
    List->elements[location].data = data;
    List->elements[location].is_used = 1;
}

int get_loc_elem(list List, int location, data_type *data) {
    if (List.elements[location].is_used == 0){
        printf("位置%d的元素不存在!\n", location);
        return false;
    } else {
        *data = List.elements[location].data;
        return true;
    }
}

void test();
int main(int argc, char **argv){
    if (DEBUG) {
        test();
    }
}

void test(){
    printf("true is %d\n", true);
    list L;
    init_list(&L);
    list_insert_loc(&L, 12, 25);
    data_type data;
    if (get_loc_elem(L, 12, &data)) {
        printf("L->elements[12].data = %d\n", data);
    }
    destroy_list(&L);
}