#define IR_LEFT 2
#define IR_FRONT 3
#define IR_RIGHT 4

#define IN1 5   // Right motor
#define IN2 6
#define IN3 7   // Left motor
#define IN4 8
#define ENA 10  // Right motor enable
#define ENB 9   // Left motor enable

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

  // Startup delay for positioning
  delay(5000);
}

void loop() {
  int left = digitalRead(IR_LEFT);
  int front = digitalRead(IR_FRONT);
  int right = digitalRead(IR_RIGHT);

  // Check if there's no obstacle ahead (front == HIGH)
  if (front == HIGH) {
    moveForward();
  }
  // Front obstacle, right is blocked → turn left
  else if (front == LOW && right == LOW && left == HIGH) {
    turnLeft();
  }
  // Front obstacle, left is blocked → turn right
  else if (front == LOW && left == LOW && right == HIGH) {
    turnRight();
  }
  // All blocked → turn around
  else if (front == LOW && left == LOW && right == LOW) {
    turnAround();
  }
  else {
    stopMotors();
  }
}

// === Motor Control ===

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  delay(300);
  stopMotors();
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  delay(300);
  stopMotors();
}

void turnAround() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  delay(500);
  stopMotors();
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
