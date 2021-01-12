#include "Thermistor.h"
#include "Arduino.h"
#include "Timer.h"
// typedef void (* CallBack)();

Thermistor::Thermistor(uint8_t pin, uint32_t referenceResistance, uint32_t nominalResistance, uint32_t nominalTemperatureCelsius, uint16_t bValue, uint16_t adcResolution) {
	_pin = pin;
  _referenceResistance = referenceResistance;
	_nominalResistance = nominalResistance;
	_nominalTemperature = celsiusToKelvins(nominalTemperatureCelsius);
	_bValue = bValue;
	_adcResolution = max(adcResolution, 0);

  pinMode(_pin = pin, INPUT);
}

/**
	Reads and returns a temperature in Celsius.
	Reads the temperature in Kelvin,
	converts in Celsius and return it.

	@return temperature in Celsius.
*/
float Thermistor::readCelsius() {
	return kelvinsToCelsius(readKelvin());
}

/**
	Returns a temperature in Fahrenheit.
	Reads a temperature in Kelvin,
	converts in Fahrenheit and return it.

	@return temperature in Fahrenheit.
*/
float Thermistor::readFahrenheit() {
	return kelvinsToFahrenheit(readKelvin());
}

/**
	Returns a temperature in Kelvin.
	Reads the thermistor resistance,
	converts in Kelvin and return it.

	@return temperature in Kelvin.
*/
float Thermistor::readKelvin() {
	return resistanceToKelvins(readResistance());
}

float Thermistor::resistanceToKelvins(float resistance) {
	float inverseKelvin = 1.0 / _nominalTemperature + log(resistance / _nominalResistance) / _bValue;
	return (1.0 / inverseKelvin);
}

float Thermistor::readResistance() {
	return _referenceResistance / (_adcResolution / readVoltage() - 1);
}

float Thermistor::readVoltage() {
	return analogRead(_pin);
}

float Thermistor::celsiusToKelvins(float celsius) {
	return (celsius + 273.15);
}

float Thermistor::kelvinsToCelsius(float kelvins) {
	return (kelvins - 273.15);
}

float Thermistor::celsiusToFahrenheit(float celsius) {
	return (celsius * 1.8 + 32);
}

/**
	Kelvin to Fahrenheit conversion:
	F = (K - 273.15) * 1.8 + 32
	Where C = (K - 273.15) is Kelvins To Celsius conversion.
	Then F = C * 1.8 + 32 is Celsius to Fahrenheit conversion.
	=> Kelvin convert to Celsius, then Celsius to Fahrenheit.
*/
float Thermistor::kelvinsToFahrenheit(float kelvins) {
	return celsiusToFahrenheit(kelvinsToCelsius(kelvins));
}

uint8_t Thermistor::getPin(void) {
  return  _pin;
}