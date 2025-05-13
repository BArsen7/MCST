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
        //printf("*%s*, %d\n", buf, read);
        if (read > 0 && buf[read-1] == '\n') {
            buf[read-1] = '\0';
            read--;
        }
        for (int i = 0; i<read; i++){
            if (isprint(buf[i]) && buf[i]!='\n' && buf[i]!=' ') fl =1;
        }
        if (fl){ 
            List *p = realloc(*list, (*strings_counter+1)*sizeof(List));
            if (p!=NULL){
                //*(strchr(buf, '\n')) = '\0'; 
                p[*strings_counter].str = strdup(buf);
                p[*strings_counter].len = read;
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


int sort_by_len(const void *A, const void *B){
    return ((List *) A)->len - ((List *) B)->len;
}

int sort_by_len_reversed(const void *A, const void *B){
    return sort_by_len(B,A);
}

int sort_by_litografy(const void *A, const void *B){
    return strcmp(((List *)A)->str, ((List *)B)->str);
}

int sort_by_litografy_reversed(const void *A, const void *B){
    return sort_by_litografy(B,A);
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
    if ((fpw=fopen(argv[2],"w")) == NULL) { 
        printf("Не удается открыть файл %s\n", argv[2]); 
        exit(2); 
    }
    
    List *buffer;
    int strings_counter;
    
    //чтение
    read(fpr, &buffer, &strings_counter);

    //сортировка
    printf("sorted %s\n", argv[3]);
    if (strcmp(argv[3], "by_len") == 0){
        qsort(buffer, strings_counter, sizeof(List), &sort_by_len); 
    } else if (strcmp(argv[3], "by_len_r") == 0){
        qsort(buffer, strings_counter, sizeof(List), &sort_by_len_reversed); 
    } else if (strcmp(argv[3], "by_lit") == 0) {
        qsort(buffer, strings_counter, sizeof(List), &sort_by_litografy);
    } else if (strcmp(argv[3], "by_lit_r") == 0) {
        qsort(buffer, strings_counter, sizeof(List), &sort_by_litografy_reversed);
    }
    
    for(int i = 0; i<strings_counter; i++){
        printf("%s\n", buffer[i].str);
        fprintf(fpw, "%s\n", buffer[i].str);
    }

    if (fclose(fpr) != 0) printf("Ошибка при закрытии файла %s\n", argv[1]); 
    if (fclose(fpw) != 0) printf("Ошибка при закрытии файла %s\n", argv[2]); 


    // Освобождение памяти
    for(int i = 0; i < strings_counter; i++) {
        free(buffer[i].str);
    }
    free(buffer);

    return 0; 
    }
 