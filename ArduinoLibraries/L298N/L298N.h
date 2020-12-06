#ifndef _L298N_H
#define _L298N_H

#include "Arduino.h"

typedef void (* Callback)();
typedef void (* CallbackWithArgs)(uint8_t);
/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>

class L298N {

public:

L298N(uint8_t m1p, uint8_t m1a, uint8_t m1b, uint8_t m2a, uint8_t m2b, uint8_t m2p);

static const uint8_t SS = 0;
static const uint8_t FF = 1;
static const uint8_t BB = 2;
static const uint8_t LL = 3;
static const uint8_t RR = 4;
static const uint8_t FR = 5;
static const uint8_t FL = 6;
static const uint8_t BR = 7;
static const uint8_t BL = 8;


uint8_t setSpeed(uint8_t speed);
uint8_t setDrivingInterval(uint16_t drivingInterval);
uint8_t drive(uint8_t drive);
uint8_t begin();
uint8_t run();

 
private:
  uint8_t _m1p = 0,  _m1a = 0, _m1b = 0, _m2a = 0, _m2b = 0, _m2p = 0;
  uint8_t _speed = 255, _drive = 0, _turn = 150;
  uint16_t _drivingInterval = 10;

};
#endif // _L298N_H
