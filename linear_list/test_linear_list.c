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
       && linearList.elements == (ElementType *)0) {
        printf("test InitList success.\n");
    } else {
        printf("test InitList fail.\n");
        if (result != SUCCESS) {
            printf("result != SUCCESS\n");
        }
        if (linearList.length != 0) {
            printf("linearList.length != 0\n");
        }
        if (linearList.elements != (ElementType *)0) {
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
       && linearList.elements == (ElementType *)0) {
        printf("test DestroyList success.\n");
    } else {
        printf("test DestroyList fail.\n");
        if (result != SUCCESS) {
            printf("result != SUCCESS\n");
        }
        if (linearList.length != 0) {
            printf("linearList.length != 0\n");
        }
        if (linearList.elements != (ElementType *)0) {
            printf("linearList.elements != (Element*)0\n");
        }

        printf("\n");
        exit(-1);
    }
}

void test_ListInsert()
{
    LinearList linearList;

    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    if (linearList.elements[0] != 10 || linearList.length != 1) {
        printf("test ListInsert fail.\n");
        exit(-1);
    }

    ListInsert(&linearList, 1, 20);
    if (linearList.elements[0] != 20 || linearList.elements[1] != 10 || linearList.length != 2) {
        printf("test ListInsert fail.\n");
        exit(-1);
    }

    printf("test ListInsert success.\n");
}

void test_ListDelete()
{
    LinearList linearList;

    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 20);

    ElementType temp;
    ListDelete(&linearList, 2, &temp);
    if (linearList.length != 1 || temp != 10) {
        printf("test ListDelete fail.\n");
        exit(-1);
    }

    ListDelete(&linearList, 1, &temp);
    if (linearList.length !=0 || temp != 20) {
        printf("test ListDelete fail.\n");
        exit(-1);
    }

    printf("test ListDelete success.\n");
}

int main()
{
    test_InitList();
    test_DestroyList();
    test_ListInsert();
    test_ListDelete();
}