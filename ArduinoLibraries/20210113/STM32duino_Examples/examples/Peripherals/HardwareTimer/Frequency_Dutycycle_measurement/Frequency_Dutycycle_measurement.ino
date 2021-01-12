/*
  Frequency and dutycycle measurement
  This example shows how to configure HardwareTimer to measure external signal frequency and dutycycle.
  The input pin will be connected to 2 channel of the timer, one for rising edge the other for falling edge.
  Each time a rising edge is detected on the input pin, hardware will save counter value into one of the CaptureCompare register.
  Each time a falling edge is detected on the input pin, hardware will save counter value into the other CaptureCompare register.
  External signal (signal generator for example) should be connected to `D2`.

*/

#define pin  D2

uint32_t channelRising, channelFalling;
volatile uint32_t FrequencyMeasured, DutycycleMeasured, LastPeriodCapture = 0, CurrentCapture, HighStateMeasured;
uint32_t input_freq = 0;
HardwareTimer *MyTim;

/**
    @brief  Input capture interrupt callback : Compute frequency and dutycycle of input signal

*/
void TIMINPUT_Capture_Rising_IT_callback(HardwareTimer*)
{
  CurrentCapture = MyTim->getCaptureCompare(channelRising);
  /* frequency computation */
  if (CurrentCapture > LastPeriodCapture)
  {
    FrequencyMeasured = input_freq / (CurrentCapture - LastPeriodCapture);
    DutycycleMeasured = (HighStateMeasured * 100) / (CurrentCapture - LastPeriodCapture);
  }
  else if (CurrentCapture <= LastPeriodCapture)
  {
    /* 0x1000 is max overflow value */
    FrequencyMeasured = input_freq / (0x10000 + CurrentCapture - LastPeriodCapture);
    DutycycleMeasured = (HighStateMeasured * 100) / (0x10000 + CurrentCapture - LastPeriodCapture);
  }

  LastPeriodCapture = CurrentCapture;
}


/**
    @brief  Input capture interrupt callback : Compute frequency and dutycycle of input signal

*/
void TIMINPUT_Capture_Falling_IT_callback(HardwareTimer*)
{
  /* prepare DutyCycle computation */
  CurrentCapture = MyTim->getCaptureCompare(channelFalling);

  if (CurrentCapture > LastPeriodCapture)
  {
    HighStateMeasured = CurrentCapture - LastPeriodCapture;
  }
  else if (CurrentCapture <= LastPeriodCapture)
  {
    /* 0x1000 is max overflow value */
    HighStateMeasured = 0x10000 + CurrentCapture - LastPeriodCapture;
  }
}


void setup()
{
  Serial.begin(115200);

  // Automatically retrieve TIM instance and channelRising associated to pin
  // This is used to be compatible with all STM32 series automatically.
  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
  channelRising = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));

  // channelRisings come by pair for TIMER_INPUT_FREQ_DUTY_MEASUREMENT mode:
  // channelRising1 is associated to channelFalling and channelRising3 is associated with channelRising4
  switch (channelRising) {
    case 1:
      channelFalling = 2;
      break;
    case 2:
      channelFalling = 1;
      break;
    case 3:
      channelFalling = 4;
      break;
    case 4:
      channelFalling = 3;
      break;
  }

  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  MyTim = new HardwareTimer(Instance);

  // Configure rising edge detection to measure frequency
  MyTim->setMode(channelRising, TIMER_INPUT_FREQ_DUTY_MEASUREMENT, pin);

  // With a PrescalerFactor = 1, the minimum frequency value to measure is : TIM counter clock / CCR MAX
  //  = (SystemCoreClock) / 65535
  // Example on Nucleo_L476RG with systemClock at 80MHz, the minimum frequency is around 1,2 khz
  // To reduce minimum frequency, it is possible to increase prescaler. But this is at a cost of precision.
  // The maximum frequency depends on processing of both interruptions and thus depend on board used
  // Example on Nucleo_L476RG with systemClock at 80MHz the interruptions processing is around 10 microseconds and thus Max frequency is around 100kHz
  uint32_t PrescalerFactor = 1;
  MyTim->setPrescaleFactor(PrescalerFactor);
  MyTim->setOverflow(0x10000); // Max Period value to have the largest possible time to detect rising edge and avoid timer rollover
  MyTim->attachInterrupt(channelRising, TIMINPUT_Capture_Rising_IT_callback);
  MyTim->attachInterrupt(channelFalling, TIMINPUT_Capture_Falling_IT_callback);

  MyTim->resume();

  // Compute this scale factor only once
  input_freq = MyTim->getTimerClkFreq() / MyTim->getPrescaleFactor();
}


void loop()
{
  /* Print frequency and dutycycle measured on Serial monitor every seconds */
  Serial.print((String)"Frequency = " + FrequencyMeasured);
  Serial.println((String)"    Dutycycle = " + DutycycleMeasured);
  delay(1000);
}