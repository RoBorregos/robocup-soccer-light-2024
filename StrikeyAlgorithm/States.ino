
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


void approachGoal() { 
    // update data from goals  
    goals.updateData(); 
    int x;  
    if (attack == Yellow) {
        x = goals.getX(1);  
    } else {
        x = goals.getX(0); 
    }
    
    if (x > 200) {
        // Goal is to the left 
        orientation_sensor.readValues(); 
        int error = pid.calculateError(orientation_sensor.getYaw(), 0); 
        robot_drive.linealMovementError(300, Constants::speed, error);  
    } else if (x < 120) {
        // Goal is to the right 
        orientation_sensor.readValues(); 
        int error = pid.calculateError(orientation_sensor.getYaw(), 0); 
        robot_drive.linealMovementError(60, Constants::speed, error);   
    } else {
        // Goal is centered 
        orientation_sensor.readValues(); 
        int error = pid.calculateError(orientation_sensor.getYaw(), 0); 
        robot_drive.linealMovementError(0, Constants::speed, error);  
    }
}  

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
    goals.initiate(); 
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
void updateGoals(){ 
    if (Serial3.available()) {
      goals.updateData();  
      for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
        int color = goals.getColor(i); 
        if (color == 1) {
            Serial.print("blue"); 
        } else if (color == 2) {
            Serial.print("yellow");
        }
      }
    } 
}     

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