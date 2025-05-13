#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    if (argc!=2){
        printf("Синтаксис команды: %s filepath\n", argv[0]); 
        exit(1); 
    }
    FILE *fp = fopen(argv[1], "r");
    if(fp==NULL){
        perror("Ошибка открытия файла");
        exit(2);
    }
    pid_t pid = fork();
    
    if (pid == 0) {
        //printf("I'm child process!\n");
        char c; 
        FILE *fpw = fopen("ChildFile.txt", "w");
        
        if(fpw==NULL){
            perror("Ошибка открытия файла");
            exit(2);
        }

        while ((c = getc(fp))!=EOF) 
            putc(c,fpw);
        
        fclose(fpw); 
    } else {
	    //printf("I'm parent process!\n");
        char c; 
        FILE *fpw = fopen("ParentFile.txt", "w");
        
        if(fpw==NULL){
            perror("Ошибка открытия файла");
            exit(2);
        }

        while ((c = getc(fp))!=EOF) 
            putc(c,fpw);
        
        fclose(fpw); 
        wait(NULL);
    }
    fclose(fp);
    return 0;
}

