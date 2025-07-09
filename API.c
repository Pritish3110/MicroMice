#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int getInteger(char* command) {
    printf("%s\n", command);
    fflush(stdout);
    char response[BUFFER_SIZE];
    fgets(response, BUFFER_SIZE, stdin);
    return atoi(response);
}

int getBoolean(char* command) {
    printf("%s\n", command);
    fflush(stdout);
    char response[BUFFER_SIZE];
    fgets(response, BUFFER_SIZE, stdin);
    return strcmp(response, "true\n") == 0;
}

int getAck(char* command) {
    printf("%s\n", command);
    fflush(stdout);
    char response[BUFFER_SIZE];
    fgets(response, BUFFER_SIZE, stdin);
    return strcmp(response, "ack\n") == 0;
}

int API_mazeWidth() { return getInteger("mazeWidth"); }
int API_mazeHeight() { return getInteger("mazeHeight"); }
int API_wallFront() { return getBoolean("wallFront"); }
int API_wallRight() { return getBoolean("wallRight"); }
int API_wallLeft() { return getBoolean("wallLeft"); }
int API_moveForward() { return getAck("moveForward"); }
void API_turnRight() { getAck("turnRight"); }
void API_turnLeft() { getAck("turnLeft"); }

void API_setWall(int x, int y, char d) {
    printf("setWall %d %d %c\n", x, y, d); fflush(stdout);
}
void API_clearWall(int x, int y, char d) {
    printf("clearWall %d %d %c\n", x, y, d); fflush(stdout);
}
void API_setColor(int x, int y, char c) {
    printf("setColor %d %d %c\n", x, y, c); fflush(stdout);
}
void API_clearColor(int x, int y) {
    printf("clearColor %d %d\n", x, y); fflush(stdout);
}
void API_clearAllColor() {
    printf("clearAllColor\n"); fflush(stdout);
}
void API_setText(int x, int y, char* t) {
    printf("setText %d %d %s\n", x, y, t); fflush(stdout);
}
void API_clearText(int x, int y) {
    printf("clearText %d %d\n", x, y); fflush(stdout);
}
void API_clearAllText() {
    printf("clearAllText\n"); fflush(stdout);
}
int API_wasReset() { return getBoolean("wasReset"); }
void API_ackReset() { getAck("ackReset"); }
