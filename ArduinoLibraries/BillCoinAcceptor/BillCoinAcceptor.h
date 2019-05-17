#ifndef _BILLCOINACCEPTOR_H
#define _BILLCOINACCEPTOR_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (* Callback)();

class BillCoinAcceptor {

public:
  BillCoinAcceptor(uint16_t pinCoin);
  BillCoinAcceptor(uint16_t pinCoin,  uint8_t coinValue);
  BillCoinAcceptor(uint16_t pinCoin, uint8_t coinValue, bool activeState);

  uint16_t coinPulse = 0;

  //void attach(Callback cbCoin, Callback cbCount);
  void attach(Callback cbCoin);
  void detach(void);

  void readCoinPulse(void); 

private:
  uint8_t _coinValue;
  uint8_t _pinCoin;
  uint8_t _activeState = false;
  uint8_t _index = 0;
};

#endif // _BILLCOINACCEPTOR_H
