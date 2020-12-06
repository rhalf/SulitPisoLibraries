#include "L298N.h"

L298N::L298N(uint8_t m1p, uint8_t m1a, uint8_t m1b, uint8_t m2a, uint8_t m2b,  uint8_t m2p) {
  _m1p = m1p;
  _m1a = m1a;
  _m1b = m1b;
  _m2p = m2p;
  _m2a = m2a;
  _m2b = m2b;
}

uint8_t L298N::setSpeed(uint8_t speed) {
  _speed = speed;
  Serial.println(_speed);
}

uint8_t L298N::drive(uint8_t drive) {
  _drive = drive;
}

uint8_t L298N::setDrivingInterval(uint16_t drivingInterval) {
  _drivingInterval = drivingInterval;
}

uint8_t L298N::begin() {
  pinMode(_m1p, OUTPUT);
  pinMode(_m1a, OUTPUT);
  pinMode(_m1b, OUTPUT);
  pinMode(_m2p, OUTPUT);
  pinMode(_m2a, OUTPUT);
  pinMode(_m2b, OUTPUT);
}

uint8_t L298N::run() {
  analogWrite(_m1p, _speed);
  analogWrite(_m2p, _turn);

  switch(_drive) {
    case L298N::FF:
      digitalWrite(_m1a, HIGH);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, LOW);
      Serial.println("FF");
      break;
    case L298N::BB:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, HIGH);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, LOW);
      Serial.println("BB");
      break;
    case L298N::RR:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, HIGH);
      digitalWrite(_m2b, LOW);
      Serial.println("RR");
      break;
    case L298N::LL:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, HIGH);
      Serial.println("LL");
      break;


    case L298N::FR:
      digitalWrite(_m1a, HIGH);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, HIGH);
      Serial.println("FR");
      break;
    case L298N::FL:
      digitalWrite(_m1a, HIGH);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, HIGH);
      digitalWrite(_m2b, LOW);
      Serial.println("FL");
      break;
    case L298N::BR:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, HIGH);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, HIGH);
      Serial.println("BR");
      break;
    case L298N::BL:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, HIGH);
      digitalWrite(_m2a, HIGH);
      digitalWrite(_m2b, LOW);
      Serial.println("BL");
      break;
    case L298N::SS:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, LOW);
      Serial.println("SS");
      break;
    default:
      digitalWrite(_m1a, LOW);
      digitalWrite(_m1b, LOW);
      digitalWrite(_m2a, LOW);
      digitalWrite(_m2b, LOW);
      Serial.println("SS");
      break;
  }
}
