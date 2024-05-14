#ifndef PID_h
  #define PID_h

class PID {
  private:
    double kP;
    double kI;
    double kD;
    double control_error;
    double previous_error;
    double previous_time;
    double sum_error;  
    double max_error; 

  public:
    PID(double p, double i, double d);
    double calculateError(int angle, int set_point); 
    
};

#endif