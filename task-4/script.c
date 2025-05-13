#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

// -m -c -s -t --elbrus=[1c+,2c+,2c3,4c,16c]
//prg -tm -s --elbrus=16c file0 --elbrus=2c3 file1
//prg -tm -x --elbrus=16c file0

void add(char ***p, int *len, char *data){
    char **new = realloc(*p, (*len+1) * sizeof(char*));
    if (new!=NULL){
        new[*len] = data;
        *len+=1;
        *p=new;
    } else {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    
}


int main(int argc, char *argv[]) {

    int flag_long;
    int rez;
    char **correct_options = NULL;
    char **incorrect_options = NULL;
    //char *non_options;
    int len_c = 0;
    int len_i = 0;
    //int len_n = 0;

    const char* short_options = "mcst";
 
    const struct option long_options[] = {
        { "elbrus:", 2, NULL, -2 },
        { NULL, 0, NULL, 0}
    };

    while ((rez = getopt_long(argc, argv, short_options, long_options, NULL))!=-1){
        char *buf = malloc(11*sizeof(char));
        if (buf!=NULL) 
            switch (rez) {
                case 'm': 
                    strcpy(buf, "m\0");
                    add(&correct_options, &len_c, buf); 
                    break;
                case 'c': 
                    strcpy(buf, "c\0");
                    add(&correct_options, &len_c, buf);
                    break;
                case 's': 
                    strcpy(buf, "s\0");
                    add(&correct_options, &len_c, buf); 
                    break;
                case 't': 
                    strcpy(buf, "t\0");
                    add(&correct_options, &len_c, buf); 
                    break;
                case -2: 
                    strcpy(buf, "elbrus=");
                    strcat(buf, optarg);

                    if (strcmp (buf,"1c+")==0 || strcmp (buf,"2c+")==0 || strcmp (buf,"2c3")==0 || 
                    strcmp (buf,"4c")==0 || strcmp (buf,"16c")==0) {
                        add(&correct_options, &len_c, buf);
                    } else {
                        add(&incorrect_options, &len_i, buf);
                    }

                    //printf("found argument \"elbrus = %s\"\n", optarg); 
                    break;
                case '?':
                    strcpy(buf, "m\0");
                    add(&incorrect_options, &len_i, buf); 
                    //printf("Error found !\n"); 
                    break;
                default:
                    free(buf);
                    break;
        }
    }

    if (len_c){
        printf("Correct options:");
        for (int i = 0; i < len_c; i++){
            printf(" %s;", correct_options[i]);
        }
        printf("\n");
    }
    

    if (len_i){
        printf("Incorrect options:");
        for (int i = 0; i < len_i; i++){
            printf(" %s;", incorrect_options[i]);
        }
        printf("\n");
    }

    if (optind<argc){
        printf("non-options:");
        for (int index = optind; index < argc; index++)
            printf (" %s;", argv[index]);
        printf("\n");
    }
    
    if (len_c){
        for (int i = 0; i<len_c; i++){
            free(correct_options[i]);
        }
        free(correct_options);
    }
    if (len_i){
        for (int i = 0; i<len_i; i++){
            free(incorrect_options[i]);
        }
        free(incorrect_options);
    }
    }