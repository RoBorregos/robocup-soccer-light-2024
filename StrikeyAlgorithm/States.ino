//function of ball_distcance working 
void searchBallWithDistance() { 
    // Get ball angle and modifications
    int ball_angle = ring_IR.getAngle();  
    ball_angle = (ball_angle < 0 ? 360 + ball_angle : ball_angle);   
    ball_angle = 360 - ball_angle;  
    ball_angle = ringIR.mapAngleWithOffset(ball_angle);   

    // Get ball distance 
    ball_distance = ringIR.getStrength();  

    int error = calculateError();  

    if (ball_distance == 0) {
        robot_drive.driveOff(); 
    } 

    // First scenario: ball close
    if (ball_distance > 60) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 220, error);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 50; 
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 50; 
            }
            robot_drive.linealMovementError(ball_angle, Constants::speed, error);
        }
    } 
    // Second scenario: ball far
    else if (ball_distance < 60) {
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

    // regulate speed for whent the robor its too close to the goal 

}

//function of ball_distance not working
void searchBall() {  
    // Get ball angle and modifications
    int ball_angle = ring_IR.getAngle();  
    ball_angle = (ball_angle < 0 ? 360 + ball_angle : ball_angle);   
    ball_angle = 360 - ball_angle;  
    ball_angle = ringIR.mapAngleWithOffset(ball_angle);  

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
}  


void approachGoal() { 
    // update data from goals 
    // get x, large, width from goals  
    // get PID error 

    // do something if goal its not seen 

    // if its seen, do something for going left, right o center 

    // if its too far, do something 
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
    ring_IR.initiate(&current_time) 
    ring_IR.setOffset(0.0); 
    color_sensor.initiate(); 
} 

void robotTurn() { 
    updateGoals(); 
    if ((attack == yellow && blueGoal.getWidth() > 30) || (attack == blue && yellowGoal.getWidth() > 30)) {
        orientation_sensor.setOffset(180);
    }
} 

void exitLine() {
    color_sensor.calculateDirection();  
    int control = calculateError(); 
    int angle_line = color_sensor.getDirection();  
    unsigned long previous_time = millis(); 

    while((millis() - time) < 300) {
        // ?? orientation_sensor.readValues(); 
        robot_drive.linealMovementError(angle_line, 200, control); 
    }
}

int ballDetector() {

}

void aline() {
    // ???
} 

bool inLine() { 
    if (angleLine != -1) {
        return true; 
    } else {
        return false; 
    }
} 

// Obtain and save camera data
 void updateGoals(){
    if (Serial1.available()) {
        String input1 =  Serial1.readStringUntil('\n');
        if (input1[0] == 'y') {
            yellowGoal.updateData(input1); 
        } else if (input1[0] == 'b') {
            blueGoal.updateData(input1);
        }
    }
 }