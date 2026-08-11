const int motorR1 = 12;
const int motorR2 = 14;
const int motorL2 = 27;
const int motorL1 = 26;
const int motorLS = 25;
const int motorRS = 33;
const int metaldetect = 5;
const int irobstacleR = 39;
const int irobstacleL = 36;
const int buzzer = 13;
String metal = "no"; // debounce

unsigned long last = 0; // last direction change
const long interval = 600; // # of milliseconds between switches
bool direction = false; // false = turn left, true = turn right

void MovementLoop() {
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);

  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);

  unsigned long current = millis(); //start timer. Use millis to allow sensing while moving because delay stops all functions
  //check if (interval) milliseconds has passed
  if (current - last >= interval) {
    last = current; //reset timer
    direction = !direction; //invert direction
  }
  //check direction
  if (direction == true) {
    //go right
    analogWrite(motorRS, 80);
    analogWrite(motorLS, 170); //left motor is faster for some reason. Tried to find problem and fix but found nothing. Might be internal/inside the motor housing.. I have adjusted this so many times it hurts
  } else {
    //go left
    analogWrite(motorRS, 255); //left motor is faster for some reason. Tried to find problem and fix but found nothing. Might be internal/inside the motor housing
    analogWrite(motorLS, 80);
  }
}

void AvoidObstacleR() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);

  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  analogWrite(motorRS, 150);
  analogWrite(motorLS, 255);
  delay(500);
}

void AvoidObstacleL() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);

  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  analogWrite(motorRS, 255);
  analogWrite(motorLS, 150);
  delay(500);
}

void MetalDetected() {
  metal = "yes"; // make sure it doesn't activate again (debounce)
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);

  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);

  analogWrite(buzzer, 50);
  delay(2000);
  analogWrite(buzzer, 0);
  delay(2500);

  MovementLoop(); // move forward for 1.5 seconds
  delay(1500);
  metal = "no";
}

void setup() {
  Serial.begin(9600);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorRS, OUTPUT);
  pinMode(motorLS, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(metaldetect, INPUT_PULLUP);
  pinMode(irobstacleR, INPUT);
  pinMode(irobstacleL, INPUT);
  Serial.println("Ready");
}

void loop() {
  int right = digitalRead(irobstacleR);
  int left = digitalRead(irobstacleL);

  int metald = digitalRead(metaldetect);

  if (metald == LOW && metal == "no") {
    MetalDetected();
  } else if (right == LOW) {
    AvoidObstacleR();
  } else if (left == LOW) {
    AvoidObstacleL();
  } else {
    MovementLoop();
  }
}
