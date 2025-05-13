#include <stdlib.h>
#include <getopt.h>

// -m -c -s -t --elbrus=[1c+,2c+,2c3,4c,16c]
//prg -tm -s --elbrus=16c file0 --elbrus=2c3 file1
//prg -tm -x --elbrus=16c file0


int main(int argc, char *argv[]) {
   int rez = 0;
    opterr = 0;
    while ( (rez = getopt(argc, argv, "mcst")) != -1){
        switch (rez) {
            case 'm': printf("found argument \"m\".\n"); break;
            case 'c': printf("found argument \"c\".\n"); break;
            case 's': printf("found argument \"s\".\n"); break;
            case 't': printf("found argument \"t\"\n"); break;
            case '?': printf("Error found !\n"); break;
        }
    }   
}