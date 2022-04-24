// // 2022.4 haruki1234
#include<stdio.h>
#include<stdlib.h>


int *lcode;
int fsize;


void run() {
    int clen = (fsize-5)/4;

    // 即値:0, int: 1

    int int_var[256];
    int sta[256];
    int stp = 0;
    int label[256];

    int_var[0] = 0;

    int p;
    p = 0;
    while (p<clen) {
        if (lcode[p+0]==0) { // label
            label[lcode[p+1]] = p;
        }
        p+=5;
    }
    p = 0;
    while (p<clen) {
        printf("%d ", lcode[p+0]);
        printf("%d ", lcode[p+1]);
        printf("%d ", lcode[p+2]);
        printf("%d ", lcode[p+3]);
        printf("\n");
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
                        sta[stp] = int_var[lcode[p+2]];
                    break;
                }
                stp++;
            break;
            case 8: // pop
                stp--;
                switch (lcode[p+1])
                {
                    case 1:
                        int_var[lcode[p+2]] = sta[stp];
                    break;
                }
            break;
            default:
            break;
        }
        //printf(": %d\n",int_var[0]);
        p+=4;
    }
    printf("result: %d\n",int_var[0]);
    
    return;
}

int main(int argc,char* argv[]) {
    
    FILE *fp;
    if ((fp = fopen(argv[1], "rb+")) == NULL) {
        printf("Can't open a file. : %s",argv[1]);
        return 1;
    }

    fpos_t fs;
    fseek(fp, 0, SEEK_END); // ファイルポインタを末尾へ移動
    fgetpos(fp, &fs); // ファイルポインタの位置を取得
    fsize = fs;
    fseek(fp, 0, SEEK_SET); // ファイルポインタを末尾へ移動

    lcode = (int*)malloc(fsize);

    printf("file: %d byte\n",fsize);

    char head[4];
    char f = 1;
    while (f) {
        fread(head,1,4,fp);
        fsize-=4;
        if (head[0]==0) {
            f = 0;
            break;
        }
    }
    printf("\n");
    fread(lcode,4,fsize/sizeof(int),fp);

    fclose(fp);

    run();
    return 0;
}