#ifndef _THERMISTOR_H
#define _THERMISTOR_H

#include "Timer.h"
#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
//typedef void (* CallBack)();

class Thermistor {

  public:

    Thermistor(uint8_t pin);
    Thermistor(uint8_t pin, uint32_t referenceResistance, uint32_t nominalResistance, uint32_t nominalTemperatureCelsius, uint16_t bValue, uint16_t adcResolution);


    float readCelsius();

    float readFahrenheit();

    float readKelvin();

    float resistanceToKelvins(float resistance);

    float readResistance();

    float readVoltage();

    float celsiusToKelvins(float celsius);

    float kelvinsToCelsius(float kelvins);

    float celsiusToFahrenheit(float celsius);

    float kelvinsToFahrenheit(float kelvins);

    uint8_t getPin();

  private:
    uint8_t _pin;
    uint32_t _referenceResistance;
    uint32_t _nominalResistance;
    uint32_t _nominalTemperature;
    uint32_t _nominalTemperatureCelsius;
    uint16_t _bValue;
    uint16_t _adcResolution;
};
#endif // _THERMISTOR_H
