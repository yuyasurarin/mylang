// // 2022.4 haruki1234
#include<stdio.h>

int code[6][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

void run() {
    int int_var[128];
    int sta[256];
    int stp = 0;
    int label[32];

    int p;
    p = 0;
    while (p<sizeof(code)/sizeof(code[0])) {
        if (code[p][0]==0) { // label
            label[code[p][1]] = p;
        }
        p++;
    }
    
    return;
}

void main() {
    printf("a");
    run();
    return;
}