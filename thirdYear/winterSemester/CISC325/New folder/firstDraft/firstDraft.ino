void setup() {
  //put your setup code here, to run once:
  //set up pin modes
  //move arm to start position
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // wait for pi input
  Serial.println("Hello");
  String wallPosCol;
  String wallPosRow;
  
  if(RECIVED TXMSION){
    // UPDATE ALL INFO FROM 8X8 TO 10X10
    
    if(capture == 1){
      String wallPos = findNearestWall(new_col, new_row);
      if(wallPos.equals("bottom"){
        wallPosCol = new_col;
        wallPosRow = 0;
      }
      else if(wallPos.equals("top"){
        wallPosCol = new_col;
        walPosRow = 9;
      }
      else if(wallPos.equals("left"){
        wallPosCol = 0;
        wallPosRow = new_row;
      }
      else{
        wallPosCol = 9;
        wallPosRow = new_row;
      }
      
    }
    moveArm(new_col, new_row, piece, capture);
    magnetOn();
    moveArm(wallPosCol, wallPosRow, new_col, piece, capture);
    magnetOff();
  
    moveArm(orig_col, orig_row, piece, capture);
    magnetOn();
    moveArm(new_col, new_row, piece, capture); 
    }
  
}

String findNearestWall(new_col, new_row){
  bottomDis = new_row;
  leftDis = new_col;
  rightDis = 7 - new_col;
  topDis = 7 - bottomDis;

  shortestVertDis = min(bottomDis,topDis);
  shortestHorDis = min(leftDis, rightDis);

  shortestDis = min(shortestVertDis, shortestHorDis);

  if(shortestDis == bottomDis)
      return "bottom";
  else if(shortestDis == topDis)
    return "top";
  else if(shortestDis == "leftDis)
    return "left";
  else
    return "right";
}
