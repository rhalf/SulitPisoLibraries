/*
  Input capture
  This example shows how to configure HardwareTimer in inputcapture to measure external signal frequency.
  Each time a rising edge is detected on the input pin, hardware will save counter value into CaptureCompare register.
  External signal (signal generator for example) should be connected to `D2`.
  Measured frequency is displayed on Serial Monitor.
*/

#define pin  D2

uint32_t channel;
volatile uint32_t FrequencyMeasured, LastCapture = 0, CurrentCapture;
uint32_t input_freq = 0;
HardwareTimer *MyTim;

void InputCapture_IT_callback(HardwareTimer*)
{
  CurrentCapture = MyTim->getCaptureCompare(channel);
  /* frequency computation */
  if (CurrentCapture > LastCapture) {
    FrequencyMeasured = input_freq / (CurrentCapture - LastCapture);
  }
  else if (CurrentCapture <= LastCapture) {
    /* 0x1000 is max overflow value */
    FrequencyMeasured = input_freq / (0x10000 + CurrentCapture - LastCapture);
  }
  LastCapture = CurrentCapture;
}


void setup()
{
  Serial.begin(115200);

  // Automatically retrieve TIM instance and channel associated to pin
  // This is used to be compatible with all STM32 series automatically.
  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
  channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));

  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  MyTim = new HardwareTimer(Instance);

  // Configure rising edge detection to measure frequency
  MyTim->setMode(channel, TIMER_INPUT_CAPTURE_RISING, pin);

  // With a PrescalerFactor = 1, the minimum frequency value to measure is : TIM counter clock / CCR MAX
  //  = (SystemCoreClock) / 65535
  // Example on Nucleo_L476RG with systemClock at 80MHz, the minimum frequency is around 1,2 khz
  // To reduce minimum frequency, it is possible to increase prescaler. But this is at a cost of precision.
  // The maximum frequency depends on processing of the interruption and thus depend on board used
  // Example on Nucleo_L476RG with systemClock at 80MHz the interruption processing is around 4,5 microseconds and thus Max frequency is around 220kHz
  uint32_t PrescalerFactor = 1;
  MyTim->setPrescaleFactor(PrescalerFactor);
  MyTim->setOverflow(0x10000); // Max Period value to have the largest possible time to detect rising edge and avoid timer rollover
  MyTim->attachInterrupt(channel, InputCapture_IT_callback);
  MyTim->resume();

  // Compute this scale factor only once
  input_freq = MyTim->getTimerClkFreq() / MyTim->getPrescaleFactor();
}


void loop()
{
  /* Print frequency measured on Serial monitor every seconds */
  Serial.println((String)"Frequency = " + FrequencyMeasured);
  delay(1000);
}