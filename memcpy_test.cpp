//
// Created by baiguiren on 10/21/16.
//

#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <zconf.h>
#include <sys/timeb.h>

long long getSystemTime() {
    struct timeb t;
    ftime(&t);
    return 1000*t.time + t.millitm;
}

int main(){
    long long start = getSystemTime();

    int a[1000000]={0};

    int b[10] = {0,1,2,3,4,5,6,7,8,9};
    printf("b[1]=%d\n", b[1]);
    memcpy(b, &b[5], 5);
    printf("b[1]=%d\n", b[1]);
    /*
    for (int i = 0; i < 999998; ++i) {
        a[i] = a[i+1];
    }
    for (int i = 0; i < 999998; ++i) {
        a[i] = a[i+1];
    }
    for (int i = 0; i < 999998; ++i) {
        a[i] = a[i+1];
    }
    for (int i = 0; i < 999998; ++i) {
        a[i] = a[i+1];
    }
     */
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);
    memcpy(a, &a[1], 999998);

    long long end = getSystemTime();
    printf("run time: %lld\n", end-start);

    return 0;
}