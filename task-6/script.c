#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    if (argc!=2){
        printf("Синтаксис команды: %s filepath\n", argv[0]); 
        exit(1); 
    }
    struct stat *buf;
    if (stat (argv[1], buf)==0){
        printf("ИНформация о файле:\n");
        printf("Размер файла: %d байт\n");
    }else {
        perror("Ошибка");
    }
    
    

    return 0;
}