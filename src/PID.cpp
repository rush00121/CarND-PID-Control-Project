#include <uWS/WebSocketProtocol.h>
#include <uWS/WebSocket.h>
#include "PID.h"
#include "json.hpp"
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->p_error = 0 ;
    this->d_error = 0 ;
    this->i_error = 0 ;
}

void PID::UpdateError(double cte) {
  this->d_error = cte - p_error;
  this->p_error = cte ;
  this->i_error = this->i_error + cte;
}

double PID::TotalError() {
  return fabs(p_error) + fabs(i_error) + fabs(d_error);
}
void PID::twiddle(double tolerance, double cte) {

  double p[] = {Kp,Kd,Ki};
  double dp[] = {p_error, d_error,i_error};
  iterations++;

  std::cout<<"Kp:"<<Kp<<" Ki:"<<Ki<<" Kd:"<<Kd<<" error:"<<bestError<<" i:"<<twiddle_param<<endl;

  if (fabs(dp[0]) + fabs(dp[1]) > tolerance) {
    int i = twiddle_param ;
    switch (state){
      case 0:
        p[i] =p[i]+ dp[i];
        state = 1;
        break;
      case 1:
        if (fabs(cte) < bestError ) {
          bestError = cte;
          dp[i] = dp[i] * 1.1;
          p[i] =p[i]+ dp[i];
          twiddle_param=(twiddle_param+1)%3;
          state = 0 ;
        }else{
          p[i] = p[i] - (2 * dp[i]);
          state = 2 ;
        }
        break;
      case 2:
        if (fabs(cte) < bestError) {
          bestError = cte;
          dp[i] = dp[i] * 1.1;
          p[i] =p[i]+ dp[i];
        } else {
          dp[i] = dp[i] * 0.9;
          p[i] = p[i] +dp[i];
        }
        twiddle_param=(twiddle_param+1)%3;
        state = 0 ;
        break;
    }

    if(p[i]<0){
      p[i] = 0 ;
    }else if(p[i]>10){
      p[i]=10;
    }


    /**
     * Limit the range of Kp and Kd for quicker convergence
     */

    if(i==0){
      if(p[i]>0.5){
        p[i]=0.5;
      }
    }

    if(i==1){
      if(p[i]<5){
        p[i]=5;
      }
    }

    if(i==2) {
      if(p[i]>0.001){
        p[i]=0.01;
      }
    }

    Kp = p[0];
   // Ki = p[1];
    Kd = p[1];

    Ki = p[2];

  } else {
    std::cout<<"*****************Final Params****** = KP:" << Kp << " KI:" << Ki << " KD:" <<Kd <<endl;
  }

}


void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}




