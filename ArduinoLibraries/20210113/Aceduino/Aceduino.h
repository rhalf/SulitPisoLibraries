#ifndef _ACEDUINOTRAINER_H
#define _ACEDUINOTRAINER_H

#include "AceduinoTrainer.h"
#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (* Callback)();

class AceduinoTrainer {

public:
  const uint8_t BUZZER = 4;
  const uint8_t[] RGB = {5, 6, 9};
  const uint8_t[] LEDS = {11, 12, 13, 14, 15, 16, 17, 18};
  const uint8_t[] DIGITS = {10, 8, 7};
  const uint8_t BUTTONS = {2, 3};
  const uint8_t DS18B20 = 19;

  AceduinoTrainer();

  void begin();

  void onButton1(uint8_t edge, Callback callback); 
  void onButton2(uint8_t edge, Callback callback);

  void setRGB(uint8_t red, uint8_t green, uint8_t blue);
  void setLed(uint8_t data);
  void setDigit1();
  void setDigit2();
  void setDigit3();
  float getTemperature();

private:
  uint8_t _index = 0;
  uint8_t _rgb = {0,0,0};
  uint8_t _led = 0;
  uint32_t _7s_data = 0;
  uint8_t _7s_digit = 0;

  Callback _cbButton1 = NULL;
  Callback _cbButton2 = NULL;
};
#endif // _ACEDUINOTRAINER_H
