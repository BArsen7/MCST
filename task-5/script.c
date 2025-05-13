#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main (){
    FILE *fp = fopen("random-file", "r");
    
    if(fp){
        fclose(fp);
    } else {
        return errno;
    }
    return 0;
}
