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

// define boolean values
#define TRUE 1
#define FALSE 0

void handleInterruption(int);
void printBigCharacter(char);
void printInvalidArgsError();
void printInvalidColorError(char[]);
void displayTime();
void printHelp();
int setColor(char[]);
void resetColor();

time_t currentTime; // variable to keep the current time

int main(int argc, char ** argv) {

    char color[128] = "white"; //  setting default color
    int isHelpNeeded = FALSE, isInvalidArgs = FALSE; // variables to keep track of the help/error message
    int index = 1; // variable to track the args positions

    // checking the arguments
    while (index < argc) {
        if (strlen(argv[index]) >= 2) {
            if (argv[index][0] == '-' && argv[index][1] == 'c') {   // if the argument starts with '-c'
                if (strlen(argv[index]) == 2) { // when argument is exactly '-c'
                    if (index == argc - 1) {    // if there are no more arguments
                        isInvalidArgs = TRUE;
                        index++;
                        continue;
                    } else {
                        strcpy(color, argv[index + 1]); // use the next argument as the color
                        index = index + 2;  // to skip the next argument
                        continue;
                    }
                } else {    // when argument starts with '-c' but not exactly '-c'
                    int c = 0;
                    int l = strlen(argv[index]) - 2;
                    char str[l];

                    // extract the next part of the argument
                    while (c < l) {
                        str[c] = argv[index][c + 2];
                        c++;
                    }
                    str[l] = '\0';
                    strcpy(color, str); // use the extracted part as the color
                    index++;
                    continue;
                }
            } else if (argv[index][0] == '-' && argv[index][1] == 'h') {    // if the argument starts with '-h'
                isHelpNeeded = TRUE;
                index++;
                continue;
            } else if (strlen(argv[index]) == 2 && argv[index][0] == '-' && argv[index][1] == '-') {    // if the argument is '--'
                index++;
                break;
            } else if (argv[index][0] == '-') { // if the argument starts with '-' but not exactly '--' (note: when argument length >=2)
                isInvalidArgs = TRUE;
                index++;
                break;
            }
            index++;    // skip all other argument types with length>=2
        }
        index++;    // skip all other argument types with length<2
    }

    // check for errors and print the relevant error messages if there are any
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

    signal(SIGINT, handleInterruption); // handle the interruption

    printf("\e[?25l");  // make the cursor invisible
    printf("\e[?47h");  // save the current screen
    printf("\e7");      // save the current cursor position
    printf("\e[H");     // move the cursor to home position
    printf("\e[J");     // clear the screen

    time(&currentTime);
    while (TRUE) {
        displayTime();
    }

    return 0;
}

// function to check and set the color mode
// returns 1 if successful
// returns 0 if unsuccessful
int setColor(char color[]) {
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
    time(&currentTime); // set the current time
    struct tm tm = *localtime(&currentTime);
    char *timestr = asctime(&tm);
    printf("\e[1B\e[1C");   // set the top and left margins (by moving the cursor)
    for (int i = 11; i <= 18; i++) {
        printBigCharacter(timestr[i]);  // print the number in block characters
        printf("\e[5A\e[1C");   // move the cursor to the next starting position
    }
    printf("\e[6B\e[31D");  // move the cursor to the starting position of date
    printf("%d-%.2d-%.2d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);   // print the date
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
void printInvalidColorError(char color[]) {
    printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", color);
}

// function to terminate the program when Ctrl+C is pressed
void handleInterruption(int signum) {
    printf("\e8"); // restore cursor
    printf("\e[?47l"); // restore screen
    printf("\e[?25h"); // make cursor visible
    resetColor(); // reset the color
    exit(0); // terminate the program
}

// function to print a given character (number or colon sign) with block characters
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