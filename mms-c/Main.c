#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "API.h"

#define MAZE_SIZE 16
#define INF 255

int flood[MAZE_SIZE][MAZE_SIZE];
bool visited[MAZE_SIZE][MAZE_SIZE];
bool walls[MAZE_SIZE][MAZE_SIZE][4];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char dir[] = {'N', 'E', 'S', 'W'};

int x = 0, y = 0, heading = 0;

bool inBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < MAZE_SIZE && y < MAZE_SIZE;
}

void setWall(int x, int y, int d) {
    if (!inBounds(x, y)) return;
    walls[x][y][d] = true;
    API_setWall(x, y, dir[d]);
    int nx = x + dx[d];
    int ny = y + dy[d];
    if (inBounds(nx, ny)) {
        walls[nx][ny][(d + 2) % 4] = true;
    }
}

void updateWalls() {
    if (API_wallFront()) setWall(x, y, heading);
    if (API_wallLeft()) setWall(x, y, (heading + 3) % 4);
    if (API_wallRight()) setWall(x, y, (heading + 1) % 4);
}

void floodFillInit(int gx, int gy) {
    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++)
            flood[i][j] = INF;
    flood[gx][gy] = 0;
    bool updated;
    do {
        updated = false;
        for (int i = 0; i < MAZE_SIZE; i++) {
            for (int j = 0; j < MAZE_SIZE; j++) {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    if (inBounds(ni, nj) && !walls[i][j][d]) {
                        if (flood[ni][nj] + 1 < flood[i][j]) {
                            flood[i][j] = flood[ni][nj] + 1;
                            updated = true;
                        }
                    }
                }
            }
        }
    } while (updated);
}

void turnTo(int desired) {
    while (heading != desired) {
        API_turnLeft();
        heading = (heading + 3) % 4;
    }
}

void moveForward() {
    x += dx[heading];
    y += dy[heading];
    API_moveForward();
}

void step(int gx, int gy) {
    updateWalls();
    floodFillInit(gx, gy);
    int bestDir = -1, minVal = INF;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (inBounds(nx, ny) && !walls[x][y][d] && flood[nx][ny] < minVal) {
            bestDir = d;
            minVal = flood[nx][ny];
        }
    }
    if (bestDir != -1) {
        turnTo(bestDir);
        moveForward();
    }
}

bool at(int tx, int ty) {
    return x == tx && y == ty;
}

void stepWithHighlight(int gx, int gy, int* steps) {
    updateWalls();
    floodFillInit(gx, gy);
    int bestDir = -1, minVal = INF;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (inBounds(nx, ny) && !walls[x][y][d] && flood[nx][ny] < minVal) {
            bestDir = d;
            minVal = flood[nx][ny];
        }
    }
    if (bestDir != -1) {
        API_setColor(x, y, 'G');
        turnTo(bestDir);
        moveForward();
        (*steps)++;
    }
}


int main() {
    int gx = 7, gy = 7;
    API_clearAllColor();

    while (!at(gx, gy)) step(gx, gy);
    API_setText(x, y, "Goal");

    int sx = 0, sy = 0;
    while (!at(sx, sy)) step(sx, sy);

    int steps = 0;
    while (!at(gx, gy)) stepWithHighlight(gx, gy, &steps);

    char buf[20];
    sprintf(buf, "Steps: %d", steps);
    API_setText(0, 0, buf);
}
