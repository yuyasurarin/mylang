// // 2022.4 haruki1234

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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

//

int exponentiation(int x,int n) {
    int result = 1;
    for (int i=0;i<n;i++) {
        result *= x;
    }
    return result;
}
int toint(char *str) {
    int len = strlen(str);
    int ret = 0;
    for (int i=0;i<len;i++) {
        if ((str[i]-48)>0&&(str[i]-48)<10) {
            ret += (str[i]-48)*exponentiation(10,len-i-1);
        }
    }
    return ret;
}
int texttonum(char *str) {
    int len = strlen(str);
    int ret = 0;
    for (int i=0;i<len;i++) {
        ret += (str[i]-48)*exponentiation(74,len-i-1);
    }
    return ret;
}
void lntrim(char *str) {
    int i = 0;
    while(1) {
        if(str[i] == '\r') {
            str[i] = '\0';
        }
        if(str[i] == '\0') {
            break;
        }
        i++;
    }
}

int main(int argc,char* argv[]) {
    clock_t sc = clock();
    time_t st = time(NULL);
    
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
    char str[1024];
    sprintf(str,"%s %s\n %s","nlmc",argv[1],ctime(&st));

    char endhead[8] = {0,0,0,0,0,0,0,0};
    fwrite(&str, sizeof(char), strlen(str), fp2);
    if (strlen(str)%4==0) {
        fwrite(&endhead, sizeof(char), 4, fp2);
    }
    else {
        fwrite(&endhead, sizeof(char), 8-(strlen(str))%4, fp2);
    }

    char *dst[10];
    char *arg[10];
	char line[maxl];
    while (fgets(line, maxl, fp) != NULL) {
        int code[4] = {1,1,0,0};
        lntrim(line);
        if (strlen(line)<1||line[0]==';') {
            continue;
        }
        int count = split(dst,line,' ');
        count = split(arg,dst[2],',');

        int cmpr = 2;
        if (strncmp(dst[0],"label",cmpr)==0) code[0] = 0;
        else if (strncmp(dst[0],"set",cmpr)==0) code[0] = 1;
        else if (strncmp(dst[0],"mov",cmpr)==0) code[0] = 2;
        else if (strncmp(dst[0],"add",cmpr)==0) code[0] = 3; // 加算
        else if (strncmp(dst[0],"sub",cmpr)==0) code[0] = 4; // 減算
        else if (strncmp(dst[0],"mul",cmpr)==0)code[0] = 5; // 乗算
        else if (strncmp(dst[0],"div",cmpr)==0) code[0] = 6; // 除算
        else if (strncmp(dst[0],"push",cmpr)==0) code[0] = 7;
        else if (strncmp(dst[0],"pop",cmpr)==0) code[0] = 8;
        else if (strncmp(dst[0],"jmp",cmpr)==0) code[0] = 9;
        else if (strncmp(dst[0],"jpc",cmpr)==0) code[0] = 10;
        else if (strncmp(dst[0],"equ",cmpr)==0) code[0] = 100; // 等しい ==
        else if (strncmp(dst[0],"nequ",cmpr)==0) code[0] = 101; // 等しくない !=
        else if (strncmp(dst[0],"gtr",cmpr)==0) code[0] = 102; // より大きい >
        else if (strncmp(dst[0],"les",cmpr)==0) code[0] = 103; // より小さい <
        else if (strncmp(dst[0],"geq",cmpr)==0) code[0] = 104; // 以上 >=
        else if (strncmp(dst[0],"leq",cmpr)==0) code[0] = 105; // 以下 <=
        else code[0] = -1;
        
        cmpr = 2;
        if (strncmp(dst[1],"int",cmpr)==0) code[1] = 1;
        else code[1] = toint(dst[1]);

        code[2] = toint(arg[0]);
        code[3] = toint(arg[1]);

        fwrite(&code, sizeof(int), 4, fp2);
    }
    printf("\n");

    
    int code[4] = {-1,0,0,0};
    fwrite(&code, sizeof(int), 2, fp2);

    int fsize;
    if (fseek(fp2, 0L, SEEK_END) == 0) {
        fpos_t pos;
        if (fgetpos(fp2, &pos) == 0) {
            fsize = (int)pos;
        }
    }

    printf("file: %d byte\n",fsize);

    fclose(fp2);

    time_t et = time(NULL);
    clock_t ec = clock();
    
    printf("time: %d\n",et-st);
    printf("time: %f\n",ec-sc);


    return 0;
}
