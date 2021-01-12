#include "BillCoinAcceptor.h"
#include "Arduino.h"

typedef void (* Callback)();

BillCoinAcceptor::BillCoinAcceptor(uint16_t pin) {
    _pin = pin;
    _multiplier = 1;
    if (_activeState) {
        pinMode(_pin, INPUT);
    } else {
        pinMode(_pin, INPUT_PULLUP);
    }
}

BillCoinAcceptor::BillCoinAcceptor(uint16_t pin, uint8_t multiplier) {
    _pin = pin;
    _multiplier = multiplier;
    if (_activeState) {
        pinMode(_pin, INPUT);
    } else {
        pinMode(_pin, INPUT_PULLUP);
    }
}

BillCoinAcceptor::BillCoinAcceptor(uint16_t pin, uint8_t multiplier, bool activeState) {
    _pin = pin;
    _multiplier = multiplier;
    _activeState = activeState;

    if (_activeState) {
        pinMode(_pin, INPUT);
    } else {
        pinMode(_pin, INPUT_PULLUP);
    }
}

void BillCoinAcceptor::attach(Callback callBack) {
    if (_activeState) {
         attachInterrupt(digitalPinToInterrupt(_pin), callBack, RISING);
    } else {
         attachInterrupt(digitalPinToInterrupt(_pin), callBack, FALLING);
    }
}

void BillCoinAcceptor::detach(void) {
    detachInterrupt(digitalPinToInterrupt(_pin));
}

void BillCoinAcceptor::readPulse(void) {
    // invalidate signals beyond minimum interval
    for (_index = 0; _index < interval; _index++) {
        if (digitalRead(_pin) != _activeState) return;
        else delay(1);
    }    
    pulse += 1;
    value = pulse * _multiplier;
}

void BillCoinAcceptor::clear(void) {
    pulse = 0;;
    value = 0;
}