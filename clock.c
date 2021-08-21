#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc > 3) {
        printf("Invalid argument count\n");
        return 0;
    } else if(argc == 3) {
        if(0 != strcmp(argv[1], "-c")){
            printf("Invalid input\n");
            return 0;
        }
        printf("colour is %s.\n", argv[2]);
    } else if(argc == 2) {
        if(0 != strcmp(argv[1], "-h")){
            printf("Invalid input\n");
            return 0;
        }
        printf("help");
        return 0;
    }

    return 0;
}