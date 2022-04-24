// // 2022.4 haruki1234
#include<stdio.h>
#include<stdlib.h>

#define maxl 256


// https://qiita.com/fireflower0/items/dc54f3ec1b3698a98b14
int isDelimiter(char p, char delim){
  return p == delim;
}

int split(char *dst[], char *src, char delim){
  int count = 0;

  for(;;) {
    while (isDelimiter(*src, delim)){
        src++;
    }
    if (*src == '\0') break;
    dst[count++] = src;
    while (*src && !isDelimiter(*src, delim)) {
      src++;
    }
    if (*src == '\0') break;
    *src++ = '\0';
  }
  return count;
}


int main(int argc,char* argv[]) {

    
    FILE *fp;
    if ((fp = fopen(argv[1], "rb+")) == NULL) {
        printf("Can't open a file. : %s",argv[1]);
        return 1;
    }
    FILE *fp2;
    if ((fp2 = fopen(argv[2], "wb+")) == NULL) {
        printf("Can't open a file. : %s",argv[2]);
        return 1;
    }
    char endhead[8] = {0,0,0,0,0,0,0,0};
    char str[] = "nlmc0";
    fwrite(&str, sizeof(char), sizeof(str), fp2);
    fwrite(&endhead, sizeof(char), 8-(sizeof(str))%4, fp2);

    char *dst[6];
    char *arg[4];
	char line[maxl];
    while (fgets(line, maxl, fp) != NULL) {
        printf("%s ",line);
        int code[5] = {0,0,0,0};

        int count = split(dst,line,' ');
        printf("%s\n",dst[0]);
        printf("%s\n",dst[1]);
        {
            int count = split(arg,dst[2],',');
            printf("%s\n",arg[0]);
            printf("%s\n",arg[1]);
        }

        fwrite(&code, sizeof(int), 4, fp2);
    }
    printf("\n");

    int fsize;
    if (fseek(fp2, 0L, SEEK_END) == 0) {
        fpos_t pos;
        if (fgetpos(fp2, &pos) == 0) {
            fsize = (int)pos;
        }
    }

    printf("file: %d byte\n",fsize);

    fclose(fp2);

    return 0;
}
