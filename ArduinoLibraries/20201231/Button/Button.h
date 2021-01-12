#ifndef _BUTTON_H
#define _BUTTON_H

#include "Arduino.h"


typedef void (* Callback)();
typedef void (* CallbackWithArgs)(uint8_t);
/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>

class Button {

public:

Button(uint8_t pin);
Button(uint8_t pin, uint8_t activeState);

void setActiveState(uint8_t activeState);
void run(void);
bool getState(void);
uint8_t getPin(void);

void setOnShortPressed(CallbackWithArgs callbackWithArgs);
void setOnLongPressed(CallbackWithArgs callbackWithArgs);

 
private:
  CallbackWithArgs _onShortPressed;
  CallbackWithArgs _onLongPressed;

  uint8_t _pin;
  bool _state = false;
  bool _activeState = false;
  bool _previousState = false;

  uint32_t _startTime = 0;
  uint32_t _shortTime = 0;
  uint32_t _longTime = 1500;


};
#endif // _BUTTON_H
