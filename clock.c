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

    printf("\e[?25l"); // make cursor invisible
    printf("\e[?47h"); // save screen
    printf("\e7"); // save cursor position
    printf("\e[H"); // move cursor to home position
    printf("\e[J"); // clear screen

    for(int i=0;i<300000;i++){
        printf("This will be the time")
        printf("\e[H"); // move cursor to home position
    }

    printf("\e8"); // restore cursor
    printf("\e[?47l"); // restore screen
    printf("\e[?25h"); // make cursor visible

    return 0;
}