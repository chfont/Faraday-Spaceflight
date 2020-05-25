#include "engine.hpp"


namespace engine {

  /* NOTE: constants in this file are named for clarity, but are optimized by the compiler into literal constants, for speed */
  
  double getForceValue(unsigned long time){
    
    //Constants for cutoff times
    const int CUTOFF_A = 300;
    const int CUTOFF_B = 1000;
    const int CUTOFF_C = 2380;
    
    if(time < CUTOFF_A) {
      return forceComponentOne(time/1000.0);
    } else if (time <  CUTOFF_B) {
      return forceComponentTwo(time/1000.0);
    } else if (time < CUTOFF_C) {
      return forceComponentThree(time/1000.0);
    } else {
      return forceComponentFour(time/1000.0);
    }
  }

  double forceComponentOne(double x){
    const double A = 114.4947;
    const double B = 0.0393;
    return A * x + B;
  }
  
  double forceComponentTwo(double x){
    const double A = 84.2139;
    const double B = -125.0071;
    const double C = 53.7142;
    return (A * pow(x,2))+ (B * x) + C;
  }

  double forceComponentThree(double x){
    const double A = 0.0076;
    const double B = 9.9181;
    return A * x + B;
  }

  double forceComponentFour(double x){
    const double A = -161.8900;
    const double B = 395.1514;
    return A * x + B;
  }
}
