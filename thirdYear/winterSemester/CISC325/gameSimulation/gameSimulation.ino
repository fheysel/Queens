#define EN        8

//Direction pin
#define X_DIR     5
#define Y_DIR     6
#define Z_DIR     7

//Step pin
#define X_STP     2
#define Y_STP     3
#define Z_STP     4

int loopCount = 0;



//DRV8825
int stps = 6400; // Steps in one rev
int tileStep = 6400 * 0.75; // Steps to move one tile


void step(boolean dir, byte dirPin, byte stepperPin, int steps) {
  int delayTime = 80;
  if(stepperPin == 4){ //if moving in z direction set speed faster
    delayTime = 30;
  }

  digitalWrite(dirPin, dir);

  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(delayTime);

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(delayTime);

  }
}


void stepDiagonally(boolean dir1, byte dirPin1, byte stepperPin1, boolean dir2, byte dirPin2, byte stepperPin2, int steps) {
  int delayTime = 80;
  
  digitalWrite(dirPin1, dir1);
  digitalWrite(dirPin2, dir2);

  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin1, HIGH);
    digitalWrite(stepperPin2, HIGH);

    delayMicroseconds(delayTime);

    digitalWrite(stepperPin1, LOW);
    digitalWrite(stepperPin2, LOW);

    delayMicroseconds(delayTime);

  }

}

void magnet(bool pos){
  step(pos, Z_DIR, Z_STP, stps*0.25);
}

void setup() {
  Serial.begin(115200);


  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

}

void moveArm(int x1, int y1, int x2, int y2, int order){
  int amountToMoveX = x2 - x1;
  int amountToMoveY = y2 - y1;
  int xDir, yDir;
  
  if(amountToMoveX < 0){
    xDir = true;
    amountToMoveX = abs(amountToMoveX);
  }
  else{
    xDir = false;
  }

  if(amountToMoveY < 0){
    yDir = false;
    amountToMoveY = abs(amountToMoveY);
  }
  else{
    yDir = true;
  }
  
  if(order == 0){
    step(xDir, X_DIR, X_STP, amountToMoveX*tileStep);
    step(yDir, Y_DIR, Y_STP, amountToMoveY*tileStep);  
  }
  else if(order == 1){
    step(yDir, Y_DIR, Y_STP, amountToMoveY*tileStep);
    step(xDir, X_DIR, X_STP, amountToMoveX*tileStep);  
  }
  else{
    stepDiagonally(xDir, X_DIR, X_STP, yDir, Y_DIR, Y_STP, amountToMoveX*tileStep);
  }

  
  
}

void loop() {
  if(loopCount == 0){
    magnet(0);
    moveArm(1, 1, 4, 2, 0);
    
    magnet(1);
    moveArm(4, 2, 4, 3, 0);
    
    magnet(0);
    moveArm(4, 3, 2, 8, 0);
    
    magnet(1);
    step(false, X_DIR, X_STP, tileStep*0.6);
    step(false, Y_DIR, Y_STP, tileStep*2);
    step(false, X_DIR, X_STP, tileStep*0.4);
    
    magnet(0);
    moveArm(3, 6, 3, 1, 0);
    
    magnet(1);
    stepDiagonally(false, X_DIR, X_STP, true, Y_DIR, Y_STP, 5*tileStep);

    delay(2000);  

    moveArm(8, 6 , 9, 6, 1);
    
    step(true, Z_DIR, Z_STP, stps*0.25);
    moveArm(9, 6, 7, 7, 0);
    
    step(false, Z_DIR, Z_STP, stps*0.25);
    
    stepDiagonally(false, X_DIR, X_STP, false, Y_DIR, Y_STP, tileStep);
    
    
  }
  while(1){
    //do nothing
  }
  loopCount++;
}
