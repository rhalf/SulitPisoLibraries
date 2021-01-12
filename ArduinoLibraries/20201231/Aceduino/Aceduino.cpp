#include "AceduinoTrainer.h"
#include "Arduino.h"

typedef void (*Callback)();

AceduinoTrainer::AceduinoTrainer() {
  pinMode(BUZZER, OUTPUT);
  for (_index = 0; _index < sizeof(RGB), _index++) pinMode(RGB[_index], OUTPUT);
  for (_index = 0; _index < sizeof(LEDS), _index++)
    pinMode(LEDS[_index], OUTPUT);
  for (_index = 0; _index < sizeof(DIGITS), _index++)
    pinMode(DIGITS[_index], OUTPUT);
  for (_index = 0; _index < sizeof(BUTTONS), _index++)
    pinMode(BUTTONS[_index], OUTPUT);

  // const uint8_t DS18B20 = 19;
}

void AceduinoTrainer::begin() {}

void AceduinoTrainer::onButton1(uint8_t edge, Callback callback) {
  attachInterrupt(0, edge, callback);
}
void AceduinoTrainer::onButton2(uint8_t edge, Callback callback) {
  attachInterrupt(1, edge, callback);
}

void AceduinoTrainer::setRGB(uint8_t red, uint8_t green, uint8_t blue){
  digitalWrite(RGB[0], red);
  digitalWrite(RGB[1], green);
  digitalWrite(RGB[2], blue);
}

void AceduinoTrainer::setLed(uint8_t data) {
  for (_index = 0; _index < 8; _index++)
    digitalWrite(LEDS[_index], bitRead(data, _index));
}

void setDigit1();
void setDigit2();
void setDigit3();