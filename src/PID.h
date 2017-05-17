#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  double Kp_tw;
  double Ki_tw;
  double Kd_tw;

  double dpp;
  double dpi;
  double dpd;

  int twiddle_param ;

  int state ;

  double bestError = 9999;

  long iterations = 0 ;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void twiddle(double tolerance,double cte);
  void Restart(uWS::WebSocket<1> ws);
};

#endif /* PID_H */
