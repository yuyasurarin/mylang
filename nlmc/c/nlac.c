// // 2022.4 haruki1234
#include<stdio.h>
#include<stdlib.h>


int code[][5] = {{5,0,0,0,0},{2,0,0,0,5},{6,0,0,0,2},{7,1,0,1,0},{4,1,0,0,1},{4,1,0,0,5}};
int lcode[1024];

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

int main() {

    codetl();
    
    FILE *fp;
    if ((fp = fopen("a:/mylang/code.bin", "wb+")) == NULL) {
        printf("Can't open a file.");
        return 1;
    }
    char endhead[8] = {0,0,0,0,0,0,0,0};
    char str[] = "hello ";
    fwrite(&str, sizeof(char), sizeof(str), fp);
    fwrite(&endhead, sizeof(char), 8-(sizeof(str))%4, fp);
    fwrite(&lcode, sizeof(int), sizeof(code)/sizeof(code[0])*5, fp);

    int fsize;
    if (fseek(fp, 0L, SEEK_END) == 0) {
        fpos_t pos;
        if (fgetpos(fp, &pos) == 0) {
            fsize = (int)pos;
        }
    }

    printf("file: %d byte\n",fsize);

    fclose(fp);

    return 0;
}