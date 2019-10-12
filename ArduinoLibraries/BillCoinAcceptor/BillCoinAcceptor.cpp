#include "BillCoinAcceptor.h"
#include "Arduino.h"

typedef void (* Callback)();

BillCoinAcceptor::BillCoinAcceptor(uint16_t pinCoin) {
    _pinCoin = pinCoin;
    _coinValue = 1;
    if (_activeState) {
        pinMode(_pinCoin, INPUT);
    } else {
        pinMode(_pinCoin, INPUT_PULLUP);
    }
}

BillCoinAcceptor::BillCoinAcceptor(uint16_t pinCoin, uint8_t coinValue) {
    _pinCoin = pinCoin;
    _coinValue = coinValue;
    if (_activeState) {
        pinMode(_pinCoin, INPUT);
    } else {
        pinMode(_pinCoin, INPUT_PULLUP);
    }
}

BillCoinAcceptor::BillCoinAcceptor(uint16_t pinCoin, uint8_t coinValue, bool activeState) {
    _pinCoin = pinCoin;
    _coinValue = coinValue;
    _activeState = activeState;

    if (_activeState) {
        pinMode(_pinCoin, INPUT);
    } else {
        pinMode(_pinCoin, INPUT_PULLUP);
    }
}

void BillCoinAcceptor::attach(Callback cbCoin) {
    if (_activeState) {
         attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, RISING);
    } else {
         attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, FALLING);
    }
}

void BillCoinAcceptor::detach(void) {
    detachInterrupt(digitalPinToInterrupt(_pinCoin));
}

void BillCoinAcceptor::readCoinPulse(void) {
    //looping for 15ms
    for (_index = 0; _index < 10; _index++) {
        if (digitalRead(_pinCoin) != _activeState) return;
        else delay(1);
    }    
    coinPulse += _coinValue;
}