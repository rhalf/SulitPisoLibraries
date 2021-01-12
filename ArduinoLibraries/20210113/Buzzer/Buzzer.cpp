#include "Buzzer.h"
#include "Arduino.h"
// typedef void (* CallBack)();

Buzzer::Buzzer(uint8_t pin, uint8_t type){
  _pin = pin;
  _type = type;
  pinMode(_pin, OUTPUT);
}

Buzzer::Buzzer(uint8_t pin){
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

Buzzer::Buzzer(void){
  pinMode(_pin, OUTPUT);
}


void Buzzer::setFrequency(uint16_t frequency) {
  _frequency = frequency;
}
void Buzzer::setTime(uint16_t time) {
  _time = time;
}

void Buzzer::play() {
  if (_type == Buzzer::ACTIVE){
    digitalWrite(_pin, HIGH);
  } else {
    tone(_pin, _frequency, _time);
  }
}

void Buzzer::stop(void) {
  if (_type == Buzzer::ACTIVE){
    digitalWrite(_pin, LOW);
  } else {
   noTone(_pin);
  }
}