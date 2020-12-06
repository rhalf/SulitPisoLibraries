#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "Timer.h"
#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
//typedef void (* CallBack)();

class Terminal {

public:

  Terminal(uint8_t pin);
  Terminal(uint8_t pin, bool activeState);

  uint32_t timeStart = 0;
  uint32_t timeEnd = 0;
  uint32_t timeLapse = 0;


  void setActiveState(bool activeState);
  bool getTimerState(void);
  bool getPinState(void);
  
  void run(void);

  void set(uint32_t second);

  void on(void);
  void off(void);

  void reset(void);

  uint8_t getPin(void);


private:
  uint8_t _pin;
  bool _activeState = false;
  bool _timerState = false;
  bool _pinState = false;
};
#endif // _TERMINAL_H
