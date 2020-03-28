#ifndef const_def_h
#define const_def_h

#define ERROR_GROUND 4
#define ERROR_IGNITE 200
#define MIN_PRESSURE 101215 //Pascals

//Pin definitions for leds + buzzer
#define redLED 9
#define greenLED 2
#define blueLED 6
#define buzzer 10


//Pyro Channels
int pyro1=20; int pyro2 = 21; int pyro3 = 22; int pyro4 = 23;
//TVC
int tvcX = 3;
int tvcY=4;


// PID Definitions
#define KIX 1
#define KIZ 1
#define KPX 1
#define KPZ 1
#define KDX 1
#define KDZ 1

#endif
