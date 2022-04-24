// // 2022.4 haruki1234
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

// http://goldilocks-engineering.blogspot.com/2015/09/c.html
// changed a little

void lntrim(char *str) {  
  int i = 0;  
  while(1) {  
    if(str[i] == '\r') {  
      str[i] = ',';  
    }
    if(str[i] == '\0') {   
      break;  
    }
    i++;  
  }  
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
    printf("%s - %d\n",str,strlen(str));
    int ret = 0;
    for (int i=0;i<len;i++) {
        ret += (str[i]-48)*exponentiation(10,len-i-1);
    }
    printf("%d\n",ret);
    return ret;
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
    char str[] = "nlmc ";
    fwrite(&str, sizeof(char), sizeof(str), fp2);
    fwrite(&endhead, sizeof(char), 8-(sizeof(str)+4)%4, fp2);

    char *dst[10];
    char *arg[10];
	char line[maxl];
    while (fgets(line, maxl, fp) != NULL) {
        int code[4] = {1,1,0,0};

        lntrim(line);
        printf("%s\n",line);
        int count = split(dst,line,' ');
        // printf("%s\n",dst[0]);
        // printf("%s\n",dst[1]);
        // {
            count = split(arg,dst[2],',');
        //     printf("%s\n",arg[0]);
        //     printf("%s\n",arg[1]);
        // }

        int cmpr = 2;
        if (strncmp(dst[0],"label",cmpr)==0) code[0] = 0;
        else if (strncmp(dst[0],"set",cmpr)==0) code[0] = 1;
        else if (strncmp(dst[0],"mov",cmpr)==0) code[0] = 2;
        else if (strncmp(dst[0],"add",cmpr)==0) code[0] = 3;
        else if (strncmp(dst[0],"sub",cmpr)==0) code[0] = 4;
        else if (strncmp(dst[0],"mul",cmpr)==0)code[0] = 5;
        else if (strncmp(dst[0],"div",cmpr)==0) code[0] = 6;
        else if (strncmp(dst[0],"push",cmpr)==0) code[0] = 7;
        else if (strncmp(dst[0],"pop",cmpr)==0) code[0] = 8;
        else code[0] = 10;

        toint(arg[1]);
        printf("%d\n",code[0]);

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

    return 0;
}
