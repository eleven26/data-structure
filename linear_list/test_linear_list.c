//
// Created by ruby on 4/22/17.
//

#include "linear_list.c"
#include <stdio.h>
#include <stdlib.h>

void test_InitList()
{
    LinearList linearList;
    Status result;
    if((result = InitList(&linearList))
       && linearList.length == 0
       && linearList.elements == (Element*)0) {
        printf("test InitList success.\n");
    } else {
        printf("test InitList fail.\n");
        if (result != SUCCESS) {
            printf("result != SUCCESS\n");
        }
        if (linearList.length != 0) {
            printf("linearList.length != 0\n");
        }
        if (linearList.elements != (Element*)0) {
            printf("linearList.elements != (Element*)0\n");
        }

        printf("\n");
        exit(-1);
    }
}

void test_DestroyList()
{
    LinearList linearList;
    Status result;

    //todo 插入数据
    if((result = DestroyList(&linearList))
       && linearList.length == 0
       && linearList.elements == (Element*)0) {
        printf("test DestroyList success.\n");
    } else {
        printf("test DestroyList fail.\n");
        if (result != SUCCESS) {
            printf("result != SUCCESS\n");
        }
        if (linearList.length != 0) {
            printf("linearList.length != 0\n");
        }
        if (linearList.elements != (Element*)0) {
            printf("linearList.elements != (Element*)0\n");
        }

        printf("\n");
        exit(-1);
    }
}

int main()
{
    test_InitList();
    test_DestroyList();
}