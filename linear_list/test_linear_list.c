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

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 20);

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

void test_ClearList()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 15);

    ClearList(&linearList);
    if (linearList.length != 0) {
        printf("test ClearList fail.\n");
        exit(-1);
    }

    printf("test ClearList success.\n");
}

void test_ListEmpty()
{
    LinearList linearList;
    InitList(&linearList);

    if (ListEmpty(&linearList) == FALSE) {
        printf("test ClearList fail.\n");
        exit(-1);
    }

    ListInsert(&linearList, 1, 10);
    if (ListEmpty(&linearList) == TRUE) {
        printf("test ClearList fail.\n");
        exit(-1);
    }

    printf("test ListEmpty success.\n");
}

void test_ListLength()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    if (ListLength(&linearList) != 1) {
        printf("test ListLength fail.\n");
        exit(-1);
    }

    ListInsert(&linearList, 1, 15);
    if (ListLength(&linearList) != 2) {
        printf("test ListLength fail.\n");
        exit(-1);
    }

    printf("test ListLength success.\n");
}

void test_GetElement()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 15);

    ElementType temp;
    GetElement(&linearList, 2, &temp);
    if (temp != 10) {
        printf("test GetElement fail.\n");
        exit(-1);
    }

    GetElement(&linearList, 1, &temp);
    if (temp != 15) {
        printf("test GetElement fail.\n");
        exit(-1);
    }

    printf("test GetElement success.\n");
}

int locateElementCompare(ElementType element1, ElementType element2)
{
    if (element1 == element2) {
        return TRUE;
    }

    return FALSE;
}

void test_LocateElement()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 15);

    size_t position;

    LocateElement(&linearList, 10, &position, locateElementCompare);
    if (position != 2) {
        printf("test LocateElement fail.\n");
        exit(-1);
    }

    LocateElement(&linearList, 15, &position, locateElementCompare);
    if (position != 1) {
        printf("test LocateElement fail.\n");
        exit(-1);
    }

    printf("test LocateElement success.\n");
}

void TraverseList(LinearList *linearList)
{
    for (int i = 0; i < linearList->length; ++i) {
        printf("%d ", linearList->elements[i]);
        if (i == linearList->length - 1) {
            printf("\n");
        }
    }
}

void test_PriorElement()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 15);
    ListInsert(&linearList, 1, 20); //[20, 15, 10]

    ElementType previous_element;
    if (PriorElement(&linearList, 20, &previous_element) == SUCCESS) {
        printf("test PriorElement fail.\n");
        exit(1);
    }

    PriorElement(&linearList, 10, &previous_element);
    if (previous_element != 15) {
        printf("%d\n", previous_element);
        printf("test PriorElement fail.\n");
        exit(2);
    }

    PriorElement(&linearList, 15, &previous_element);
    if (previous_element != 20) {
        printf("test PriorElement fail.\n");
        exit(3);
    }

    printf("test PriorElement success.\n");
}

void test_NextElement()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 10);
    ListInsert(&linearList, 1, 15);
    ListInsert(&linearList, 1, 20); //[20, 15, 10]

    ElementType next_element;
    if (NextElement(&linearList, 10, &next_element) == SUCCESS) {
        printf("test NextElement fail.\n");
        exit(1);
    }

    NextElement(&linearList, 15, &next_element);
    if (next_element != 10) {
        printf("test NextElement fail.\n");
        exit(2);
    }

    NextElement(&linearList, 20, &next_element);
    if (next_element != 15) {
        printf("test NextElement fail.\n");
        exit(3);
    }

    printf("test NextElement success.\n");
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

Status EveryBiggerThanTen(ElementType element)
{
    return element <= 10 ? FALSE : TRUE;
}

void test_ListTraverse()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 11);
    ListInsert(&linearList, 1, 20);

    ListTraverse(&linearList, EveryBiggerThanTen);

    printf("test ListTraverse success.\n");
}

void test_PrintList()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 11);
    ListInsert(&linearList, 1, 20);
    ListInsert(&linearList, 1, 30);
    ListInsert(&linearList, 1, 78);
    ListInsert(&linearList, 1, 90);
    ListInsert(&linearList, 1, 73);

    PrintList(&linearList);
    printf("test PrintList success.\n");
}

void test_DivideLinearList()
{
    LinearList linearList;
    InitList(&linearList);

    ListInsert(&linearList, 1, 11);
    ListInsert(&linearList, 1, 20);
    ListInsert(&linearList, 1, 30);
    ListInsert(&linearList, 1, 78);
    ListInsert(&linearList, 1, 90);
    ListInsert(&linearList, 1, 73);
    ListInsert(&linearList, 1, 33);
    ListInsert(&linearList, 1, 87);
    ListInsert(&linearList, 1, 23);
    ListInsert(&linearList, 1, 22);


}

int main()
{
    test_InitList();
    test_DestroyList();
    test_ListInsert();
    test_ListDelete();
    test_ClearList();
    test_ListEmpty();
    test_ListLength();
    test_GetElement();
    test_LocateElement();
    test_PriorElement();
    test_NextElement();
    test_ListTraverse();

    test_PrintList();
}