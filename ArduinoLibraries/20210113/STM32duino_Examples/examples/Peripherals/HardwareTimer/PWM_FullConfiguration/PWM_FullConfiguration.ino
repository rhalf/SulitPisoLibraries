/*
  PWM full configuration
  This example shows how to fully configure a PWM with HardwareTimer.
  PWM is generated on `LED_BUILTIN` if available.
  PWM is generated by hardware: no CPU load.
  Nevertheless, in this example both interruption callback are used on Compare match (Falling edge of PWM1 mode) and update event (rising edge of PWM1 mode).
  Those call back are used to toggle a second pin: `pin2`.
  Once configured, there is only CPU load for callbacks executions.
*/

// 'pin' PWM will be mangaed automatically by hardware whereas 'pin2' PWM will be managed by software through interrupt callback
#if defined(LED_BUILTIN)
#define pin  LED_BUILTIN

#if LED_BUILTIN == D3
#error LED_BUILTIN == D3
#else
#define pin2  D3
#endif

#else
#define pin  D2
#define pin2  D3
#endif

void Update_IT_callback(HardwareTimer*)
{ // Update event correspond to Rising edge of PWM when configured in PWM1 mode
  digitalWrite(pin2, LOW); // pin2 will be complementary to pin
}

void Compare_IT_callback(HardwareTimer*)
{ // Compare match event correspond to falling edge of PWM when configured in PWM1 mode
  digitalWrite(pin2, HIGH);
}

void setup()
{
  // No need to configure pin, it will be done by HardwareTimer configuration
  // pinMode(pin, OUTPUT);

  // Need to configure pin2, as it is not managed by HardwareTimer
  pinMode(pin2, OUTPUT);

  // Automatically retrieve TIM instance and channel associated to pin
  // This is used to be compatible with all STM32 series automatically.
  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));


  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);

  MyTim->setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
  // MyTim->setPrescaleFactor(8); // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  MyTim->setOverflow(100000, MICROSEC_FORMAT); // 10000 microseconds = 10 milliseconds
  MyTim->setCaptureCompare(channel, 50, PERCENT_COMPARE_FORMAT); // 50%
  MyTim->attachInterrupt(Update_IT_callback);
  MyTim->attachInterrupt(channel, Compare_IT_callback);
  MyTim->resume();
}


void loop()
{
  /* Nothing to do all is done by hardware. Even no interrupt required. */
}