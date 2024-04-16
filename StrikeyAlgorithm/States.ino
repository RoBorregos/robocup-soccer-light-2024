/*bool isInLine() {  
    color_sensor.calculateDirection(); 
    int angleLine = color_sensor.getDirection(); 
    if (angleLine != -1) {
        return true; 
    } else {
        return false; 
    }
} */

//function of ball_distcance working 
void searchBallWithDistance() { 
    // Get ball angle and modifications 
    ring_IR.updateData();  
    int ball_angle = ring_IR.getAngle();
    int ball_distance = ring_IR.getStrength();  
    ball_angle = (ball_angle < 0 ? 360 + ball_angle : ball_angle);   
    ball_angle = 360 - ball_angle;  
    ball_angle = ring_IR.mapAngleWithOffset(ball_angle);   

    int error = calculateError();  

    // First scenario: ball close
    if (ball_distance > 40) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 240, error);  
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 70; 
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 70; 
            }
            robot_drive.linealMovementError(ball_angle, Constants::speed, error);
        }
    } 

    // Second scenario: ball far
    else if (ball_distance < 40) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 220, error); 
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 25;
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 25; 
            }
            robot_drive.linealMovementError(ball_angle, Constants::speed, error); 
        }
    } 
     // regulate speed for whent the robot its too close to the goal  
     // check if the robot its getting inside area if speed is not regulted in here
    // This will be done in approachGoal 
    // if ball is in zero and far from goal, metele roboverguiza 
    // if ball is in zero and close from goal, decrease speed (maybe stop?)
    // if ball is not in zero, move in linealMovementError to the ball angle received from above
    
    // last position seen ? 

}

/*
void approachGoal() { 
    // update data from goals  
    //updateGoals();  

    // get x, large, width from goals   
    //int goalY = (attack == yellow) ? yellowGoal.getX() : blueGoal.getX();
    
    // get PID error 
    int error = calculateError();  
    // here the robot is centered , check for goal AND line detection, shouldnt be because exit line comes first 
    if (goalY < 110 &&) {
        robot_drive.linealMovementError(0, 220, control); 
    } else {
        robot_drive.linealMovementError(180, 180, control);
    }
    // do something if goal its not seen 

    // if its seen, do something for going left, right 
}  */

// Calculate PID error
double calculateError() {
    orientation_sensor.readValues(); 
    double control = pid.calculateError(orientation_sensor.getYaw(), 0);  
    return control; 
} 

void initializeObjects() {
    orientation_sensor.initialize(); 
    robot_drive.initialize(); 
    ring_IR.initiate(&current_time); 
    ring_IR.setOffset(0.0); 
    color_sensor.initiate(); 
    //yellowGoal.initiate(); 
    blueGoal.initiate(); 
} 

/*
void robotTurn() { 
    updateGoals(); 
    if ((attack == yellow && blueGoal.getWidth() > 30) || (attack == blue && yellowGoal.getWidth() > 30)) {
        orientation_sensor.setOffset(180);
    } // i dont know how this would work 
} */

void exitLine() {
  color_sensor.calculateDirection();  
  int angle_line = color_sensor.getDirection();     
  unsigned long time = millis(); 

  while((millis() - time) < 350) {
      // in calculate error you already take this value orientation_sensor.readValues();  
      double control = calculateError(); 
      robot_drive.linealMovementError(angle_line, 240, control); 
  }
}
/*
int ballDetector() {
    // IR detetctor hasnt been integrated in robot 
} */

/*void aline() {
    // ???
} */


// Obtain and save camera data, this might have to be change depending on pixy 
/*void updateGoals(){ 
    if (Serial2.available()) {
    String input1 =  Serial2.readStringUntil('\n');

    if (input1[0] == 'a')
      porteriaAmarilla.actualizar(input1);
    else if (input1[0] == 'b')
      porteriaAzul.actualizar(input1);
  }
 } 
 */

/*
//function of ball_distance not working
void searchBall() {  
    // Get ball angle and modifications
    int ball_angle = ring_IR.getAngle();  
    ball_angle = (ball_angle < 0 ? 360 + ball_angle : ball_angle);   
    ball_angle = 360 - ball_angle;  
    ball_angle = ring_IR.mapAngleWithOffset(ball_angle);  

    int error = calculateError(); 
    if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25 )) {
        robot_drive.linealMovementError(0, 220, error);  
    } else { 
        if (ball_angle > 10 && ball_angle <= 175) {
            ball_angle += 25;      
        } else if (ball_angle >= 185 && ball_angle < 355) {
            ball_angle -= 25;
        }     
        Serial.print("ball angle:  "); 
        Serial.print(ball_angle);
        robot_drive.linealMovementError(ball_angle, Constants::speed, error);
    }
} */