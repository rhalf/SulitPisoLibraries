#ifndef _SIM800L_H
#define _SIM800L_H

#include "Arduino.h"
#include "SoftwareSerial.h"

typedef void (* Callback)();
typedef void (* CallbackWithArgs)(uint8_t);
/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>

class Sim800l : public SoftwareSerial {

public:

Sim800l(uint8_t rx, uint8_t tx);

static const uint8_t OK = 1;
static const uint8_t READY = 2;
static const uint8_t NOT_READY = 3;
static const uint8_t ERROR = 4;
static const uint8_t TIMEOUT = 5;
static const uint8_t BUSY = 6;

uint8_t waitForResult();
uint8_t waitForResult(uint32_t timeout);

uint8_t checkDevice(void);
uint8_t checkSim(void);
uint8_t checkNetwork(uint8_t *type, uint8_t *status);
uint8_t checkSignal(uint8_t *strength, uint8_t *beacon);
uint8_t sendSms(String number, String message);
// void setOnShortPressed(CallbackWithArgs callbackWithArgs);
// void setOnLongPressed(CallbackWithArgs callbackWithArgs);

 
private:
  // CallbackWithArgs _onShortPressed;
  // CallbackWithArgs _onLongPressed;
  uint8_t _lock = false;
  uint32_t _timeout = 1000;
  uint8_t _resultInt[5];
};
#endif // _SIM800L_H
