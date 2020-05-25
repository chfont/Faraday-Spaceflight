#ifndef engine_hpp
#define engine_hpp
#include <cmath>

/* engine: namespace for engine thrust calculations
 * Engine used is an E-12 6 engine
 * Constants used in function are generated from engine.m, an associated matlab script
 * Tests were run to ensure floating point precision yielded sufficient
 * accuracy. The graph is a piecewise function, and so lambda functions and
 * cutoff times are used for the individual pieces.
 */
namespace engine {

  //Function to return the estimated force of thrust at an instant, given the time in milliseconds.
  double getForceValue(unsigned long time);

  //Lambda functions to use in retrieving the force. Constants are taken from the results of the matlab script, engine.m
  double forceComponentOne(double x);
  double forceComponentTwo(double x);
  double forceComponentThree(double x);
  double forceComponentFour(double x);
  
}


#endif
