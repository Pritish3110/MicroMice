#define IR_LEFT 2
#define IR_FRONT 3
#define IR_RIGHT 4

#define IN1 5    // Right motor
#define IN2 6
#define IN3 7    // Left motor
#define IN4 8
#define ENA 10   // Right motor enable
#define ENB 9    // Left motor enable

#define MAZE_SIZE 8
#define INF 255

uint8_t flood[MAZE_SIZE][MAZE_SIZE];
bool visited[MAZE_SIZE][MAZE_SIZE];
bool walls[MAZE_SIZE][MAZE_SIZE][4];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int x = 0, y = 0, heading = 0;  // start at (0,0) facing North

void setup() {
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_FRONT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  delay(5000);  // allow time to position

  runFloodFill();  // Start the 3-phase run
}

void loop() {}

bool inBounds(int x, int y) {
  return x >= 0 && y >= 0 && x < MAZE_SIZE && y < MAZE_SIZE;
}

void setWall(int x, int y, int d) {
  if (!inBounds(x, y)) return;
  walls[x][y][d] = true;
  int nx = x + dx[d], ny = y + dy[d];
  if (inBounds(nx, ny)) walls[nx][ny][(d + 2) % 4] = true;
}

void updateWalls() {
  if (digitalRead(IR_FRONT)) setWall(x, y, heading);
  if (digitalRead(IR_LEFT))  setWall(x, y, (heading + 3) % 4);
  if (digitalRead(IR_RIGHT)) setWall(x, y, (heading + 1) % 4);
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
          int ni = i + dx[d], nj = j + dy[d];
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
    turnLeft();
    heading = (heading + 3) % 4;
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  delay(500);  // 1 cell move duration
  stopMotors();
  x += dx[heading];
  y += dy[heading];
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

void turnLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180); analogWrite(ENB, 180);
  delay(350);
  stopMotors();
}

void turnRight() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 180); analogWrite(ENB, 180);
  delay(350);
  stopMotors();
}

void turnAround() {
  turnLeft();
  delay(350);
  turnLeft();
}

bool at(int tx, int ty) {
  return x == tx && y == ty;
}

void step(int gx, int gy) {
  updateWalls();
  floodFillInit(gx, gy);
  int bestDir = -1, minVal = INF;

  for (int d = 0; d < 4; d++) {
    int nx = x + dx[d], ny = y + dy[d];
    if (inBounds(nx, ny) && !walls[x][y][d] && flood[nx][ny] < minVal) {
      minVal = flood[nx][ny];
      bestDir = d;
    }
  }

  if (bestDir != -1) {
    turnTo(bestDir);
    moveForward();
  }
}

void runFloodFill() {
  int gx = 3, gy = 3;  // center goal cell (adjust as needed)
  while (!at(gx, gy)) step(gx, gy);
  while (!at(0, 0)) step(0, 0);
  while (!at(gx, gy)) step(gx, gy);
}
