//
//  list.c
//  
//
//  Created by baiguiren on 8/28/16.
//
//

#include <stdio.h>

typedef int Elemtype;

typedef struct List{
    int index;
    Elemtype elem;
}List;

//构造一个空的线性表
void InitList(List L){
    L = 0;
}

//销毁线性表
void DestroyList(List L){
    L = 0;
}




int main(){
    return 0;
}