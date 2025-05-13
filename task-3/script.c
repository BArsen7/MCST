#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char *str;
    int len;
}List;

void read(FILE *fp,  List **list, int *strings_counter){
    size_t symbols_counter= 0;  //колличество символов в строке 
    int pos = 0; //позиция текущейстроки в файле
    char c;  //считываемый символ
    int read;
    char *buf; 
    while ((read = getline(&buf, &symbols_counter, fp)) != -1) {
        bool fl = 0; 
        for (int i = 0; i < symbols_counter; i++){
            if (isprint(buf[i])) fl =1;
        }
        if (fl){ 
            List *p = realloc(*list, (*strings_counter+1)*sizeof(List));
            if (p!=NULL){
                p[*strings_counter].str = strdup(buf);
                p[*strings_counter].len = symbols_counter;
                *strings_counter+=1;
                *list = p;
            } else{
                printf("Ошибка выделения памяти\n");
                exit(3);
            }
        }
        //free(buf);
    }
    //printf("%s\n", (*list)[0].str);
}

int main(int argc, char *argv[]) { 

    FILE *fpr; /* указатель на файл */ 
    FILE *fpw;
    long int count = 0; 
    if (argc != 4) { 
    printf("Синтаксис команды: %s filename_to_read filename_to_write sorting_method\n", argv[0]); 
    exit(1); 
    } 
    if ((fpr=fopen(argv[1],"r")) == NULL) { 
    printf("Не удается открыть файл %s\n", argv[1]); 
    exit(2); 
    }
    if ((fpw=fopen(argv[2],"r")) == NULL) { 
        printf("Не удается открыть файл %s\n", argv[2]); 
        exit(2); 
    }
    
    List *buffer;
    int strings_counter;
    
    read(fpr, &buffer, &strings_counter);
    

    if (fclose(fpr) != 0) printf("Ошибка при закрытии файла %s\n", argv[1]); 
    if (fclose(fpw) != 0) printf("Ошибка при закрытии файла %s\n", argv[2]); 
    free(buffer);
    return 0; 
    }
 