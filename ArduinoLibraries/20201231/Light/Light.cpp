#include "Light.h"

Light::Light(uint8_t l0, uint8_t l1, uint8_t l2, uint8_t l3, uint8_t l4, uint8_t l5,  uint8_t l6, uint8_t l7) {
  _LEDS[0] = l0;
  _LEDS[1] = l1;
  _LEDS[2] = l2;
  _LEDS[3] = l3;
  _LEDS[4] = l4;
  _LEDS[5] = l5;
  _LEDS[6] = l6;
  _LEDS[7] = l7;
}

uint8_t Light::setActiveState(uint8_t activeState) {
  _activeState = activeState;
}



uint8_t Light::begin() {
  for(uint8_t i = 0; i < sizeof(_LEDS); i++){
    pinMode(_LEDS[i], OUTPUT);
    digitalWrite(_LEDS[i], !_activeState);
  }
}

uint8_t Light::on(uint8_t index) {
  digitalWrite(_LEDS[index], _activeState);
}

uint8_t Light::off(uint8_t index) {
  digitalWrite(_LEDS[index], !_activeState);
}


uint8_t Light::toggle(uint8_t index) {
  digitalWrite(_LEDS[index], !digitalRead(_LEDS[index]));
}