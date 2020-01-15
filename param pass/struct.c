//
// Created by ruby on 2020/1/15.
//

#include <stdio.h>

typedef struct User {
    char *name;
    int age;
} User;

void test1(User user)
{
    user.name = "name1";
    printf("test1: user address = %p\n", (void*)&user);
    printf("test1: name address = %p\n", (void*)&user.name);
}

void test2(User *user)
{
    user->name = "name2";
    printf("test2: user address = %p\n", (void*)&user);
    printf("test2: user address = %p\n", (void*)&(*user));
    printf("test2: name address = %p\n", (void*)&user->name);
}

int main()
{
    User user = {.age = 23, .name = "name"};
    printf("origin: user address = %p\n", (void*)&user);
    printf("origin: name address = %p\n", (void*)&user.name);

    test1(user);
    printf("test1: user.name = %s\n", user.name);

    test2(&user);
    printf("test2: user.name = %s\n", user.name);

    return 0;
}