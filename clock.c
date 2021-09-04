#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

// define values of ANSI color modes
#define RESET 0
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

#define TRUE 1
#define FALSE 0

void handleInterruption(int);
void printBigCharacter(char);
void printInvalidArgsError();
void printInvalidColorError(char *);
void displayTime();
void printHelp();
int setColor(char *);
void resetColor();


time_t currentTime; // variable to keep the current time

int main(int argc, char ** argv) {

    char * color = "white"; //  setting default color
    int isHelpNeeded = FALSE, isInvalidArgs = FALSE;    // variables to keep track of the help/error message
    int index = 1;  // variable to track the args positions

    while (index < argc) {
        if (0 == strcmp(argv[index], "-c")) {
            if (index == argc - 1) {
                isInvalidArgs = TRUE;
                index++;
                continue;
            } else {
                color = argv[index + 1];
                index = index + 2;
                continue;
            }
        }
        if (0 == strcmp(argv[index], "-h")) {
            isHelpNeeded = TRUE;
        }
        index++;
    }

    if (isHelpNeeded) {
        resetColor();
        printHelp();
        return 0;
    } else if (isInvalidArgs) {
        resetColor();
        printInvalidArgsError();
        return 0;
    } else if (0 == setColor(color)) {
        resetColor();
        printInvalidColorError(color);
        return 0;
    }

    signal(SIGINT, handleInterruption);

    printf("\e[?25l");  // make cursor invisible
    printf("\e[?47h");  // save screen
    printf("\e7");      // save cursor position
    printf("\e[H");     // move cursor to home position
    printf("\e[J");     // clear screen

    time(&currentTime);
    while (TRUE) {
        displayTime();
    }

    return 0;
}

// function to check and set the color mode
// returns 1 if successful
// returns 0 if unsuccessful
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

// function to reset the color
void resetColor() {
    printf("\e[%dm", RESET);
}

// function to get the current time,date and display it
void displayTime() {
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

// function to print the help message
void printHelp() {
    printf("usage : clock -h            quick help on cmd\n");
    printf("usage : clock -c <color>    print clock with a color\n");
    printf("<color-black|red|green|yellow|blue|magenta|cyan|white> 	supported colors\n");
}

// function to print the invalid argument error message
void printInvalidArgsError() {
    printf("Invalid use of arguments.\n");
    printf("usage : clock -h            quick help on cmd\n");
    printf("usage : clock -c <color>    print clock with a color\n");
}

// function to print the invalid color error message
void printInvalidColorError(char * color) {
    printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", color);
}

// function to terminate the program when Ctrl+C is pressed
void handleInterruption(int signum) {
    printf("\e8"); // restore cursor
    printf("\e[?47l"); // restore screen
    printf("\e[?25h"); // make cursor visible
    printf("\e[%dm", RESET);
    exit(0);
}

// function to print a given number or colon sign with block characters
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