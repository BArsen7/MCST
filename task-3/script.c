#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) { 
    //int ch; /* текущий прочитанный символ */ 
    FILE *fpr; /* указатель на файл */ 
    FILE *fpw;
    long int count = 0; 
    if (argc != 3) { 
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
    

    
    char ch;
    while ((ch=getc(fpr)) != EOF) { 
    putc(ch, fpw); 
    count++; 
    } 
    if (fclose(fpr) != 0) printf("Ошибка при закрытии файла %s\n", argv[1]); 
    if (fclose(fpw) != 0) printf("Ошибка при закрытии файла %s\n", argv[1]); 
    printf("Файл %s содержит %ld символов.\n", argv[1], count); 
    return 0; 
    }
 