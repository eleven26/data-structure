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

    for (int j = 0; j < 100; ++j) {
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
    }

    long long end = getSystemTime();
    printf("run time: %lld\n", end-start);




    start = getSystemTime();

    for (int j = 0; j < 100; ++j) {
        memcpy(a, &a[1], 999998);
        memcpy(a, &a[1], 999998);
        memcpy(a, &a[1], 999998);
        memcpy(a, &a[1], 999998);
    }

    end = getSystemTime();
    printf("run time: %lld\n", end-start);

    return 0;
}