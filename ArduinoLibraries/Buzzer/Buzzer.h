#ifndef _BUZZER_H
#define _BUZZER_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
//typedef void (* CallBack)();

class Buzzer {

public:
  Buzzer();
  Buzzer(uint8_t pin);
  Buzzer(uint8_t pin, uint16_t frequency);
  Buzzer(uint8_t pin, uint16_t frequency, uint16_t time);

  void play(void);
  void off(void);

private:
  uint8_t _pin = 13;
  uint16_t _frequency = 1875;
  uint16_t _time = 50;

};
#endif // _BUZZER_H
