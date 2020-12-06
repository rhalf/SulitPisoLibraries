#ifndef _LIGHT_H
#define _LIGHT_H

#include "Arduino.h"

typedef void (* Callback)();
typedef void (* CallbackWithArgs)(uint8_t);
/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>

class Light {

public:

Light(uint8_t l0, uint8_t l1, uint8_t l2, uint8_t l3, uint8_t l4, uint8_t l5,  uint8_t l6, uint8_t l7);


uint8_t setActiveState(uint8_t activeState);
uint8_t begin();

uint8_t on(uint8_t index);
uint8_t off(uint8_t index);
uint8_t toggle(uint8_t index);

 
private:
  uint8_t _LEDS[8];
  uint8_t _activeState = HIGH;

};
#endif // _LIGHT_H
