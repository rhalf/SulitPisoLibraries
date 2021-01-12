#ifndef _BILLCOINACCEPTOR_H
#define _BILLCOINACCEPTOR_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (* Callback)();

class BillCoinAcceptor {

public:
  BillCoinAcceptor(uint16_t pin);
  BillCoinAcceptor(uint16_t pin,  uint8_t multiplier);
  BillCoinAcceptor(uint16_t pin, uint8_t multiplier, bool activeState);

  uint16_t pulse = 0, value = 0;
  // 15 miliseconds minimum interval
  uint16_t interval = 15; 
  //void attach(Callback cbCoin, Callback cbCount);
  void attach(Callback callBack);
  void detach(void);

  void readPulse(void); 
  void clear(void); 

private:
  uint8_t _multiplier;
  uint8_t _pin;
  uint8_t _activeState = false;
  uint8_t _index = 0;
};

#endif // _BILLCOINACCEPTOR_H
