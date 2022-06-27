#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *read_line(){
    char buf[81] = {0};
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);

        if (n < 0){
            if(!res){
                    return NULL;
            }
        } else if(n>0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len+1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n>0);

    if (len > 0){
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    //printf("res: %s", res);


    return res;
}

char *fread_line(FILE* fb){
    char buf[81] = {0};
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = fscanf(fb, "%80[^\n]", buf);

        if (n < 0){
            if(!res){
                    return NULL;
            }
        } else if(n>0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len+1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(fb, "%*c");
        }
    } while (n>0);

    if (len > 0){
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    //printf("res: %s", res);


    return res;
}

void printint(int a){
    printf("%d\n", a);
}

int checkSpace(char c){
    if(c==' ' || c=='\t'){return 1;}else{return 0;}
}

int* stringToArray(char* s, int n)
{
    //printf("%s\n", s);
    int l = strlen(s);
    int f = 0;
    int k = 0;
    int charasters = 0;
    int* answ = calloc(n, sizeof(int));
    char* word;
    for (int i = 0; i < l; i++){
        if(checkSpace(s[i])){
            if(f == 1){
                //printf("'%s' \n", word);
                answ[k]=atoi(word);
                k++;
                free(word);
                charasters = 0;
                f = 0;
                if(k==n){break;}
            }
        }else{
            f = 1;
            charasters++;
            if(charasters == 1){
                word = malloc(2*sizeof(char));
            }else{
                word = realloc(word, (charasters+1)*sizeof(char));
            }
            word[charasters-1] = s[i];
            word[charasters] = '\0';
        }
    }
     if(f == 1){
                answ[k]=atoi(word);
                k++;
                free(word);
                charasters = 0;
            }
    return answ;
}

char* readword(char* s, int* position){
    while(checkSpace(s[*position])){
        (*position)++;
    }

    int i = 0;
    char* word = NULL;
    while( !checkSpace(s[*position]) && s[*position]!='\0' ){
        i++;
        word = realloc(word, i*sizeof(char));
        word[i-1] = s[*position];
        (*position)++;
    }
    i++;
    word = realloc(word, i*sizeof(char));
    word[i-1] = '\0';
    return word;
}

int readint(int *a){
    char* s = read_line("");
    *a = atoi(s);
    free(s);
    return 0;
}


int readPositive(int *a)
{
    readint(a);
    while(*a<=0){
        printf("Enter positive number!\n");
        readint(a);
    }
    return *a;
}


int* readArray(int n)
{
    char* s = read_line();
    int* arr = stringToArray(s, n);
    free(s);
    return arr;
}



int FilenameIsValid(char* name){
    int l = strlen(name);
    int i, j;
    char c;
    for(i=0; i<l; i++){
        c = name[i];
        if(!isalpha(c) && c!='.'){
            printf("Invalid file name! Only alphabet characters allowed! \n");
            return 0;
        }
    }
    return 1;
}


//##################################### OUTPUT ##########################################################

int countDigits(int a)
{
    int k = 0;
    if (a<0){
        k++;
        a*=-1;
    }
    do{
        a = a / 10;
        k++;
    }while(a>0);
    return k;
}

void printArray(int* arr, int n)
{
    int k;
    for (int i = 0; i < n; i++){
                printf("%d", arr[i]);
                k = 6-countDigits(arr[i]);
                for(int j = 0; j < k; j++)
                {
                    printf(" ");
                }
            };
}


void printArrayFloat(float* arr, int n)
{
    int k;
    for (int i = 0; i < n; i++){
                printf("%f", arr[i]);
                printf("  ");
            };
}

void printText(char* text){
    printf("%s ", text);
}
void printInteger(int a){
    printf("%d ", a);
}

