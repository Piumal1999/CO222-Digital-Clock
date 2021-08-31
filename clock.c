#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#define RESET 0
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

void handleInterruption(int);
void printBigCharacter(char);
void printInvalidArgsError();
void printInvalidColorError(char *);
void displayTime();
void printHelp();
int setColor(char *);
void resetColor();

int main(int argc, char ** argv) {
    setColor("white");
    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-h")) {
            resetColor();
            printHelp();
            return 0;
        }
        if (0 == strcmp(argv[i], "-c")) {
            if (i == argc - 1) {
                resetColor();
                printInvalidArgsError();
                return 0;
            } else {
                char * color = argv[i + 1];
                if (0 == setColor(color)) {
                    resetColor();
                    printInvalidColorError(color);
                    return 0;
                }
            }
        }
    }

    signal(SIGINT, handleInterruption);

    printf("\e[?25l"); // make cursor invisible
    printf("\e[?47h"); // save screen
    printf("\e7"); // save cursor position
    printf("\e[H"); // move cursor to home position
    printf("\e[J"); // clear screen

    while (1) {
        displayTime();
    }

    return 0;
}

int setColor(char * color) {
    if (0 == strcasecmp(color, "black")) {
        printf("\e[%dm", BLACK);
    } else if (0 == strcasecmp(color, "red")) {
        printf("\e[%dm", RED);
    } else if (0 == strcasecmp(color, "green")) {
        printf("\e[%dm", GREEN);
    } else if (0 == strcasecmp(color, "yellow")) {
        printf("\e[%dm", YELLOW);
    } else if (0 == strcasecmp(color, "blue")) {
        printf("\e[%dm", BLUE);
    } else if (0 == strcasecmp(color, "magenta")) {
        printf("\e[%dm", MAGENTA);
    } else if (0 == strcasecmp(color, "cyan")) {
        printf("\e[%dm", CYAN);
    } else if (0 == strcasecmp(color, "white")) {
        printf("\e[%dm", WHITE);
    } else {
        return 0;
    }
    return 1;
}

void resetColor() {
    printf("\e[%dm", RESET);
}

void displayTime() {
    time_t currentTime;
    time(&currentTime);
    struct tm tm = *localtime(&currentTime);
    char *timestr = asctime(&tm);
    printf("\e[1B\e[1C");
    for (int i = 11; i <= 18; i++) {
        printBigCharacter(timestr[i]);
        printf("\e[5A\e[1C");
    }
    printf("\e[6B\e[31D");
    printf("%d-%.2d-%.2d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
    printf("\e[H"); // move cursor to home position
}

void printHelp() {
    printf("usage : clock -h            quick help on cmd\n");
    printf("usage : clock -c <color>    print clock with a color\n");
    printf("<color-black|red|green|yellow|blue|magenta|cyan|white> 	supported colors\n");
}

void printInvalidArgsError() {
    printf("Invalid use of arguments.\n");
    printf("usage : clock -h            quick help on cmd\n");
    printf("usage : clock -c <color>    print clock with a color\n");
}

void printInvalidColorError(char * color) {
    printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", color);
}

void handleInterruption(int signum) {
    printf("\e8"); // restore cursor
    printf("\e[?47l"); // restore screen
    printf("\e[?25h"); // make cursor visible
    printf("\e[%dm", RESET);
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