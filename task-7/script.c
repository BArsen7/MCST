#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    if (argc!=2){
        printf("Синтаксис команды: %s filepath\n", argv[0]); 
        exit(1); 
    }

    pid_t pid = fork();
    FILE *fp = fopen(argv[1], "r");
    if (pid == -1) {
        perror("fork failed");
        exit(3);
    }

    if (pid == 0) {
        //printf("I'm child process!\n");
        //FILE *fp = fopen(argv[1], "r");
        FILE *fpw = fopen("ChildFile.txt", "w+");
        
        if(fpw==NULL || fp ==NULL){
            perror("Ошибка открытия файла");
            exit(2);
        }

        int c;
        while ((c = getc(fp))!=EOF) 
            putc(c,fpw);

        printf("Содержимое дочернего файла:\n");
        fseek(fpw, 0, SEEK_SET);
        while ((c= getc(fpw)) != EOF) {
            printf("%c", c);
        }
        fclose(fpw); 
    } else {
	    //printf("I'm parent process!\n");

        FILE *fpw = fopen("ParentFile.txt", "w+");
        
        if(fpw==NULL || fp ==NULL){
            perror("Ошибка открытия файла");
            exit(2);
        }

        int c;
        while ((c = getc(fp))!=EOF) 
            putc(c,fpw);


        wait(NULL);

        fseek(fpw, 0, SEEK_SET);
        
        printf("\n\nРодительский файл: \n");
        while ((c= getc(fpw)) != EOF) {
            printf("%c", c);
        }
        fclose(fpw); 
    }

    

  
    fclose(fp);
    return 0;
}

