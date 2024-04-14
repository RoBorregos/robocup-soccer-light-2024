//function of ball_distcance working 
void searchBallWithDistance() { 
    // initiate ball distance, angle, PID, goalDistance (goal)
    
    ring_IR.updateData();  
    orientation_sensor.readValues(); 
    double ball_distance = ring_IR.getStrength();  
    double ball_angle = ring_IR.getAngle(); 
    double yaw = orientation_sensor.getYaw();
    double control = pid.calculateError(yaw, 0);  

    ball_angle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ball_angle = 360 - ballAngle;  
    ball_angle = ring_IR.mapAngleWithOffset(ballAngle);     

    // First scenario: ball_distance > 60 (BALL CLOSE)
    if (ball_distance > 60) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) { 
          robot_drive.linealMovementError(0, 220, control);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 70; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 70; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, 200, control);
        }
    } else if (ball_distance < 60) { // Second scenario: ball distance < 60 (BALL FAR)
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) { 
            robot_drive.linealMovementError(0, 220, control);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 25; // Adjust the angle addition to 25
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 25; // Adjust the angle subtraction to 25
            }
            robot_drive.linealMovementError(ball_angle, 200, control);
        }
    }
} 

void approachGoal(){
  // update goals 
  blueGoal.updateData();
  // get y values  
  int goalY = blueGoal.getY();   
  // get control  
  double yaw = orientation_sensor.getYaw();
  double control = pid.calculateError(yaw, 0);   
  if (goalY < 110) {
    robot_drive.linealMovementError(0, 220, control); 
  } else {
    robot_drive.linealMovementError(180, 180, control);
  }

}
