
#include <Thermistor.h>

#define SENSOR_PIN             A13
#define REFERENCE_RESISTANCE   4700
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950
#define DEFAULT_ADC_RESOLUTION 1023

Thermistor thermistor = Thermistor(
  SENSOR_PIN,
  REFERENCE_RESISTANCE,
  NOMINAL_RESISTANCE,
  NOMINAL_TEMPERATURE,
  B_VALUE,
  DEFAULT_ADC_RESOLUTION
);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // Reads temperature
  float celsius = thermistor.readCelsius();
  float kelvin = thermistor.readKelvin();
  float fahrenheit = thermistor.readFahrenheit();

  // Output of information
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(kelvin);
  Serial.print(" K, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  delay(100); // optionally, only to delay the output of information in the example.
}
