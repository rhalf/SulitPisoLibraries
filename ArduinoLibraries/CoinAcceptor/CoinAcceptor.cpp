#include "CoinAcceptor.h"
#include "Arduino.h"

typedef void (* Callback)();

CoinAcceptor::CoinAcceptor(uint16_t pinCoin) {
    _pinCoin = pinCoin;
    _coinValue = 1;
    if (_activeState) {
        pinMode(_pinCoin, INPUT);
    } else {
        pinMode(_pinCoin, INPUT_PULLUP);
    }
}

CoinAcceptor::CoinAcceptor(uint16_t pinCoin, uint8_t coinValue) {
    _pinCoin = pinCoin;
    _coinValue = coinValue;
    if (_activeState) {
        pinMode(_pinCoin, INPUT);
    } else {
        pinMode(_pinCoin, INPUT_PULLUP);
    }
}

CoinAcceptor::CoinAcceptor(uint16_t pinCoin, uint8_t coinValue, bool activeState) {
    _pinCoin = pinCoin;
    _coinValue = coinValue;
    _activeState = activeState;

    if (_activeState) {
        pinMode(_pinCoin, INPUT);
    } else {
        pinMode(_pinCoin, INPUT_PULLUP);
    }
}

// CoinAcceptor::CoinAcceptor(uint8_t pinCoin, uint8_t pinCount) {
//     _pinCoin = pinCoin;
//     _pinCount = pinCount;

//     pinMode(_pinCoin, INPUT_PULLUP);
//     pinMode(_pinCount , INPUT_PULLUP);
// }

void CoinAcceptor::attach(Callback cbCoin) {
    if (_activeState) {
         attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, RISING);
    } else {
         attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, FALLING);
    }
}

// void CoinAcceptor::attach(Callback cbCoin, Callback cbCount) {
//     attachInterrupt(digitalPinToInterrupt(_pinCoin), cbCoin, FALLING);
//     attachInterrupt(digitalPinToInterrupt(_pinCount), cbCount, FALLING);
// }


void CoinAcceptor::detach(void) {
    detachInterrupt(digitalPinToInterrupt(_pinCoin));
}

// void CoinAcceptor::detach(void) {
//     detachInterrupt(digitalPinToInterrupt(_pinCoin));
//     detachInterrupt(digitalPinToInterrupt(_pinCount ));
// }


//Uncomment when emi detected
void CoinAcceptor::readCoinPulse(void) {
    for (uint8_t interval = 0; interval < 150; interval++) {
        if (digitalRead(_pinCoin))return;
        else delayMicroseconds(1);
    }
    coinPulse += _coinValue;
}

//Uncomment when emi detected
// void CoinAcceptor::onCount(void) {
//     for (uint8_t interval = 0; interval < 10; interval++) {
//         if (digitalRead(_pinCount))return;
//             else delayMicroseconds(1);
//         }
//     valueCount++;
// }