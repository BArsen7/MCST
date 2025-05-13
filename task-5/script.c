#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main (int argc, char *argv[]){
    if (argc!=2){
        printf("Синтаксис команды: %s argument\n", argv[0]); 
        exit(1); 
    }
    FILE *fp = fopen("random-file", "r");
    
    if(fp){
        fclose(fp);
    } else {
        switch(atoi(argv[1])){
            case 0:
                return errno;
                break;
            case 1:
                char *msg = strerror(errno);
                printf("%s\n", msg);
                exit(2);
                break;
            case 2:
                perror("Не удалось открыть файл\n");
                exit(2);
                break;
        }
    }
    return 0;
}
