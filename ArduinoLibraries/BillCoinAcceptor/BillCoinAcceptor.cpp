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

// BillCoinAcceptor::BillCoinAcceptor(uint8_t pinCoin, uint8_t pinCount) {
//     _pinCoin = pinCoin;
//     _pinCount = pinCount;

//     pinMode(_pinCoin, INPUT_PULLUP);
//     pinMode(_pinCount , INPUT_PULLUP);
// }

void BillCoinAcceptor::attach(Callback cbCoin) {
    if (_activeState) {
         attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, RISING);
    } else {
         attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, FALLING);
    }
}

// void BillCoinAcceptor::attach(Callback cbCoin, Callback cbCount) {
//     attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, FALLING);
//     attachInterrupt(digitalPinToInterrupt(_pinCount), cbCount, FALLING);
// }


void BillCoinAcceptor::detach(void) {
    detachInterrupt(digitalPinToInterrupt(_pinCoin));
}

// void BillCoinAcceptor::detach(void) {
//     detachInterrupt(digitalPinToInterrupt(_pinCoin));
//     detachInterrupt(digitalPinToInterrupt(_pinCount ));
// }


//Uncomment when emi detected
void BillCoinAcceptor::readCoinPulse(void) {
    for (_index = 0; _index < 150; _index++) {
        if (digitalRead(_pinCoin))return;
        else delayMicroseconds(1);
    }
    coinPulse += _coinValue;
}

//Uncomment when emi detected
// void BillCoinAcceptor::onCount(void) {
//     for (uint8_t _index = 0; _index < 10; _index++) {
//         if (digitalRead(_pinCount))return;
//             else delayMicroseconds(1);
//         }
//     valueCount++;
// }