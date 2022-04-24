// // 2022.4 haruki1234
#include<stdio.h>
#include<stdlib.h>


int main(int argc,char* argv[]) {

    
    FILE *fp;
    if ((fp = fopen(argv[2], "wb+")) == NULL) {
        printf("Can't open a file. : %s",argv[2]);
        return 1;
    }
    char endhead[8] = {0,0,0,0,0,0,0,0};
    char str[] = "nlmc0";
    fwrite(&str, sizeof(char), sizeof(str), fp);
    fwrite(&endhead, sizeof(char), 8-(sizeof(str))%4, fp);


    int r = 0;
    while (r<100) {
        int code[5] = {0,0,0,0};
        fwrite(&code, sizeof(int), 4, fp);
        r++;
    }

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