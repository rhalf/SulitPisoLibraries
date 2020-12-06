#include "Terminal.h"
#include "Arduino.h"
#include "Timer.h"
// typedef void (* CallBack)();
Terminal::Terminal(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  off();
}

Terminal::Terminal(uint8_t pin, bool activeState) {
  _pin = pin;
  _activeState = activeState;
  pinMode(_pin, OUTPUT);
  off();
}

void Terminal::setActiveState(bool activeState){
  _activeState = activeState;
}

bool Terminal::getTimerState(void) {
  return _timerState;
}

bool Terminal::getPinState(void) {
  return _pinState;
}

void Terminal::set(uint32_t second) {
  if (_timerState) {
    timeEnd+=second;
  } else {
    timeStart = Timer::getSeconds();
    timeEnd = Timer::getSeconds() + second;
  }

  _timerState = true;
  on();
}

void Terminal::on() {
  digitalWrite(_pin, _activeState);
  _pinState = true;
}

void Terminal::off(void) {
  digitalWrite(_pin, !_activeState);
  _pinState = false;
}

void Terminal::run(void) {
    if (!_timerState) return;

    timeLapse = timeEnd - Timer::getSeconds();
    if (Timer::getSeconds() >= timeEnd) {
      reset();
    }
}

void Terminal::reset(void) {
  timeLapse = 0;
  timeStart = 0;
  timeEnd = 0;
  _timerState = false;
  off();
}

uint8_t Terminal::getPin(void) {
  return  _pin;
}