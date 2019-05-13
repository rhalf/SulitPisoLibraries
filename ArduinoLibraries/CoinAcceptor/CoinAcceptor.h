#ifndef _COINACCEPTOR_H
#define _COINACCEPTOR_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (* Callback)();

class CoinAcceptor {

public:
  CoinAcceptor(uint16_t pinCoin);
  CoinAcceptor(uint16_t pinCoin,  uint8_t coinValue);
  CoinAcceptor(uint16_t pinCoin, uint8_t coinValue, bool activeState);

  uint16_t coinPulse = 0;

  //void attach(Callback cbCoin, Callback cbCount);
  void attach(Callback cbCoin);
  void detach(void);

  void readCoinPulse(void); 

private:
  uint8_t _coinValue;
  uint8_t _pinCoin;
  uint8_t _activeState = false;
};

#endif // _COINACCEPTOR_H
