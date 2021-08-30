#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

void sighandler(int);
void printBigCharacter(char);

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

    signal(SIGINT, sighandler);

    printf("\e[?25l"); // make cursor invisible
    printf("\e[?47h"); // save screen
    printf("\e7"); // save cursor position
    printf("\e[H"); // move cursor to home position
    printf("\e[J"); // clear screen

    while (1) {
        time_t currentTime;
        time(&currentTime);
        char *timestr = asctime(localtime(&currentTime));
        printf("\e[1B\e[1C");
        for (int i = 11; i <= 18; i++) {
            printBigCharacter(timestr[i]);
            printf("\e[5A\e[1C");
        }
        printf("\e[H"); // move cursor to home position
    }

    return 0;
}

void sighandler(int signum) {
    printf("\e8"); // restore cursor
    printf("\e[?47l"); // restore screen
    printf("\e[?25h"); // make cursor visible
    exit(0);
}

void printBigCharacter(char c) {
    if (c == ':') {
        printf("    \e[1B\e[4D");
        printf(" ██ \e[1B\e[4D");
        printf("    \e[1B\e[4D");
        printf(" ██ \e[1B\e[4D");
        printf("    \e[1B");
    } else if (c == '0') {
        printf("██████\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██████\e[1B");
    } else if (c == '1') {
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B");
    } else if (c == '2') {
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("██    \e[1B\e[6D");
        printf("██████\e[1B");
    } else if (c == '3') {
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("██████\e[1B");
    } else if (c == '4') {
        printf("██  ██\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B");
    } else if (c == '5') {
        printf("██████\e[1B\e[6D");
        printf("██    \e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("██████\e[1B");
    } else if (c == '6') {
        printf("██████\e[1B\e[6D");
        printf("██    \e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██████\e[1B");
    } else if (c == '7') {
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("    ██\e[1B");
    } else if (c == '8') {
        printf("██████\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██████\e[1B");
    } else if (c == '9') {
        printf("██████\e[1B\e[6D");
        printf("██  ██\e[1B\e[6D");
        printf("██████\e[1B\e[6D");
        printf("    ██\e[1B\e[6D");
        printf("██████\e[1B");
    }
}