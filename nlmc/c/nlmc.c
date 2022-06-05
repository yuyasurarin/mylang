// // 2022.6 haruki1234
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int *lcode;
int fsize;


void run() {
    int clen = (fsize-5)/4;

    // 即値:0, int: 1

    char flag_var[256];

    int int_var[256];
    int int_sta[256];
    int int_stp = 0;
    int label[256];

    int_var[0] = 0;

    int p;
    p = 0;
    while (p<clen) {
        printf("%d ", lcode[p+0]);
        printf("%d ", lcode[p+1]);
        printf("%d ", lcode[p+2]);
        printf("%d ", lcode[p+3]);
        printf("\n");
        if (lcode[p+0]==0) { // label
            label[lcode[p+1]] = p;
        }
        p+=4;
    }
    p = 0;
    while (p<clen) {
        switch (lcode[p+0])
        {
            case 1: // set
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] = lcode[p+3];
                    break;
                }
            break;
            case 2: // mov
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] = int_var[lcode[p+3]];
                    break;
                }
            break;
            case 3: // add
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] += int_var[lcode[p+3]];
                    break;
                }
            break;
            case 4: // sub
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] -= int_var[lcode[p+3]];
                    break;
                }
            break;
            case 5: // mul
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] *= int_var[lcode[p+3]];
                    break;
                }
            break;
            case 6: // div
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] = int_var[lcode[p+2]]/int_var[lcode[p+3]];
                    break;
                }
            break;
            case 7: // push
                switch (lcode[p+1])
                {
                    case 1:
                        int_sta[int_stp] = int_var[lcode[p+2]];
                        int_stp++;
                    break;
                }
            break;
            case 8: // pop
                switch (lcode[p+1])
                {
                    case 1:
                        int_stp--;
                        int_var[lcode[p+2]] = int_sta[int_stp];
                    break;
                }
            break;
            case 9: // jmp
                p = label[lcode[p+1]];
            break;
            case 10: // jpc
                if (flag_var[1]==1) {
                    p = label[lcode[p+1]];
                }
            break;

            case 100: // equ
                if (int_var[lcode[p+2]]==int_var[lcode[p+3]]) flag_var[1] = 1;
                else flag_var[1] = 0;
            break;
            case 101: // nequ
                if (int_var[lcode[p+2]]!=int_var[lcode[p+3]]) flag_var[1] = 1;
                else flag_var[1] = 0;
            break;
            case 102: // gtr
                if (int_var[lcode[p+2]]>int_var[lcode[p+3]]) flag_var[1] = 1;
                else flag_var[1] = 0;
            break;
            case 103: // les
                if (int_var[lcode[p+2]]<int_var[lcode[p+3]]) flag_var[1] = 1;
                else flag_var[1] = 0;
            break;
            case 104: // geq
                if (int_var[lcode[p+2]]>=int_var[lcode[p+3]]) flag_var[1] = 1;
                else flag_var[1] = 0;
            break;
            case 105: // leq
                if (int_var[lcode[p+2]]<=int_var[lcode[p+3]]) flag_var[1] = 1;
                else flag_var[1] = 0;
            break;

            default:
            break;
        }
        //printf(": %d\n",int_var[0]);
        p+=4;
    }
    printf("\n");
    printf("result: %d\n",int_var[0]);
    
    return;
}

int main(int argc,char* argv[]) {
    clock_t sc = clock();
    time_t st = time(NULL);
    
    FILE *fp;
    if ((fp = fopen(argv[1], "rb+")) == NULL) {
        printf("Can't open a file. : %s",argv[1]);
        return 1;
    }
    printf("file : %s",argv[1]);

    fpos_t fs;
    fseek(fp, 0, SEEK_END); // ファイルポインタを末尾へ移動
    fgetpos(fp, &fs); // ファイルポインタの位置を取得
    fsize = fs;
    fseek(fp, 0, SEEK_SET); // ファイルポインタを末尾へ移動

    lcode = (int*)malloc(fsize);

    printf(" , %d byte\n",fsize);

    printf("\n");
    char head[5];
    char f = 1;
    while (f) {
        fread(head,1,4,fp);
        fsize-=4;
        if (head[0]==0) {
            f = 0;
            break;
        }
        else {
            printf("%s",head);
        }
    }
    printf("\n");
    printf("\n");
    fread(lcode,4,fsize/sizeof(int),fp);
    fclose(fp);

    run();

    time_t et = time(NULL);
    clock_t ec = clock();
    
    printf("time: %d\n",et-st);
    printf("time: %f\n",ec-sc);
    return 0;
}