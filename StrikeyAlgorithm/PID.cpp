#include "Arduino.h"
#include "PID.h"

PID::PID(double p, double i, double d) 
  : kP(p), kI(i), kD(d), control_error(0), previous_error(0), previous_time(0), sum_error(0) {}

double PID::calculateError(int angle, int set_point) {
    // get current time in milliseconds
    unsigned long time = millis();

    // time difference since last calculation
    double delta_time = (time - previous_time) / 1000.0;

    control_error = set_point - angle;
    double delta_error = (control_error - previous_error) / delta_time;
    sum_error += control_error * delta_time;

    // calculate the control signal using PID
    double control = (kP * control_error) + (kI * sum_error) + (kD * delta_error);

    // update previous error and time
    previous_error = control_error;
    previous_time = time;

    Serial.print("Error: ");
    Serial.println(control);

    return control;
}

