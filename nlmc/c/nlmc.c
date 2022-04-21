// // 2022.4 haruki1234
#include<stdio.h>

int *code[5] = {{1,0,0,0,0},{2,0,0,0,5},{6,0,0,0,2},{7,1,0,1,0},{4,1,0,0,1}};
//int code[2][5] = {{1,1,1,1,1},{1,1,1,1,1}};

int lcode[100];

void codetl() {
    int r = 0;
    while (r<sizeof(code)/sizeof(code[0])) {
        int i = r*5;
        lcode[i+0] = code[r][0];
        lcode[i+1] = code[r][1];
        lcode[i+2] = code[r][2];
        lcode[i+3] = code[r][3];
        lcode[i+4] = code[r][4];
        r++;
    }
}

void run() {
    int clen = sizeof(code)/sizeof(code[0]);

    // 即値:0, int: 1

    int int_var[256];
    int sta[256];
    int stp = 0;
    int label[256];

    int_var[0] = 0;

    int p;
    p = 0;
    while (p<clen) {
        if (code[p][0]==0) { // label
            label[code[p][1]] = p;
        }
        p++;
    }
    p = 0;
    while (p<clen) {
        switch (code[p][0])
        {
            case 1: // mov
                switch (code[p][1])
                {
                    case 0:
                        int_var[code[p][3]] = code[p][4];
                    break;
                    case 1:
                        int_var[code[p][3]] = int_var[code[p][4]];
                    break;
                }
            break;
            case 2: // add
                switch (code[p][1])
                {
                    case 0:
                        int_var[code[p][3]] += code[p][4];
                    break;
                    case 1:
                        int_var[code[p][3]] += int_var[code[p][4]];
                    break;
                }
            break;
            case 3: // sub
                switch (code[p][1])
                {
                    case 0:
                        int_var[code[p][3]] -= code[p][4];
                    break;
                    case 1:
                        int_var[code[p][3]] -= int_var[code[p][4]];
                    break;
                }
            break;
            case 4: // mul
                switch (code[p][1])
                {
                    case 0:
                        int_var[code[p][3]] *= code[p][4];
                    break;
                    case 1:
                        int_var[code[p][3]] *= int_var[code[p][4]];
                    break;
                }
            break;
            case 5: // div
                switch (code[p][1])
                {
                    case 0:
                        int_var[code[p][3]] = int_var[code[p][3]]/code[p][4];
                    break;
                    case 1:
                        int_var[code[p][3]] = int_var[code[p][3]]/int_var[code[p][4]];
                    break;
                }
            break;
            case 6: // push
                switch (code[p][1])
                {
                    case 0:
                        sta[stp] = code[p][4];
                    break;
                    case 1:
                        sta[stp] = int_var[code[p][4]];
                    break;
                }
                stp++;
            break;
            case 7: // pop
                stp--;
                switch (code[p][1])
                {
                    case 1:
                        int_var[code[p][3]] = sta[stp];
                    break;
                }
            break;
        }
        //printf(": %d\n",int_var[0]);
        p++;
    }
    printf("result: %d",int_var[0]);
    
    return;
}

int main() {

    codetl();
    
    FILE *fp;
    if ((fp = fopen("a:/mylang/code.bin", "wb+")) == NULL) {
        printf("Can't open a file.");
        return 1;
    }

    char endhead[4] = {0,0,0,0};
    char str[] = "test";
    fwrite(&str, sizeof(char), sizeof(str), fp);
    fwrite(&endhead, sizeof(char), 3-(sizeof(str)-1)%4, fp);
    fwrite(&lcode, sizeof(int), sizeof(code)/sizeof(code[0])*5, fp);

    // int fsize;
    // if (fseek(fp, 0L, SEEK_END) == 0) {
    //     fpos_t pos;
    //     if (fgetpos(fp, &pos) == 0) {
    //         fsize = (int)pos;
    //     }
    // }

    // printf("file: %d byte\n",fsize);
    //fread(&a,sizeof(int),fsize)

    fclose(fp);


    run();
    return 0;
}