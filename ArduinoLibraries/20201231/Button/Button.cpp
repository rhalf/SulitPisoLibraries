#include "Button.h"
#include "Arduino.h"
#include "Timer.h"


Button::Button(uint8_t pin) {
  _pin = pin;

  if (_activeState)  pinMode(_pin, INPUT);
  else pinMode(_pin, INPUT_PULLUP);
}

Button::Button(uint8_t pin, uint8_t activeState) {
  _pin = pin;
  _activeState = activeState;

  if (_activeState)  pinMode(_pin, INPUT);
  else pinMode(_pin, INPUT_PULLUP);
}

void Button::setActiveState(uint8_t activeState) {
  _activeState = activeState;
  _previousState = false;
}

bool Button::getState(void) {
  if (digitalRead(_pin) == _activeState) {
    return true;
  }
  return false;
}

uint8_t Button::getPin(void) {
  return  _pin;
}

void Button::setOnShortPressed(CallbackWithArgs callbackWithArgs) {
  _onShortPressed = callbackWithArgs;
}

void Button::setOnLongPressed(CallbackWithArgs callbackWithArgs) {
  _onLongPressed = callbackWithArgs;
}

void Button::run() {
  if (getState() != _previousState && getState() == true) {
    _startTime = Timer::getMillis();
  } else if (getState() != _previousState && getState() == false) {
    uint32_t time = Timer::getMillis() - _startTime;
    if (time > _shortTime && time < _longTime) {
      //shortPress
      if (_onShortPressed != 0)
        _onShortPressed(getPin());
    } else if (time > _longTime) {
      //longPress
      if (_onLongPressed != 0)
      _onLongPressed(getPin());
    }
  }
  _previousState = getState();
}