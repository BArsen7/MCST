#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

// -m -c -s -t --elbrus=[1c+,2c+,2c3,4c,16c]
//prg -tm -s --elbrus=16c file0 --elbrus=2c3 file1
//prg -tm -x --elbrus=16c file0


int main(int argc, char *argv[]) {

    int flag_long;
    int rez;
 
    const char* short_options = "mcst";
 
    const struct option long_options[] = {
        { "elbrus:", 2, NULL, -2 },
        { NULL, 0, NULL, 0}
    };
 
    while ((rez = getopt_long(argc, argv, short_options,
        long_options, NULL))!=-1){
        switch (rez) {
        case 'm': printf("found argument \"m\"\n"); break;
        case 'c': printf("found argument \"c\"\n"); break;
        case 's': printf("found argument \"s\"\n"); break;
        case 't': printf("found argument \"t\"\n"); break;
        case -2: printf("found argument \"elbrus = %s\"\n", optarg); break;
        case '?': printf("Error found !\n"); break;
        }
    }
    for (int index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
}