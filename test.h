//
// Created by ruby on 07/05/2017.
//

#ifndef DATA_STRUCTURE_TEST_H
#define DATA_STRUCTURE_TEST_H

#endif //DATA_STRUCTURE_TEST_H

#include <stdio.h>
#include <stdlib.h>

void test_fail(char *message)
{
    printf("test %s fail.\n", message);
    exit(1);
}

void test_success(char *message)
{
    printf("test %s success.\n", message);
}