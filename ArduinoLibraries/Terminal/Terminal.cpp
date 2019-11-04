#include "Terminal.h"
#include "Arduino.h"
#include "Timer.h"
// typedef void (* CallBack)();

Terminal::Terminal(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  off();
}

void Terminal::setActiveState(bool activeState){
  _activeState = activeState;
}

bool Terminal::getState(void) {
  return _state;
}

void Terminal::set(uint32_t second) {
  if (_state) {
    timeEnd+=second;
  } else {
    timeStart = Timer::getSeconds();
    timeEnd = Timer::getSeconds() + second;
  }

  _state = true;
  on();
}

void Terminal::on() {
  digitalWrite(_pin, _activeState);
}

void Terminal::off(void) {
  digitalWrite(_pin, !_activeState);
}

void Terminal::run(void) {
    if (!_state) return;

    timeLapse = timeEnd - Timer::getSeconds();
    if (Timer::getSeconds() >= timeEnd) {
      reset();
    }
}

void Terminal::reset(void) {
  timeLapse = 0;
  timeStart = 0;
  timeEnd = 0;
  _state = false;
}

uint8_t Terminal::getPin(void) {
  return  _pin;
}