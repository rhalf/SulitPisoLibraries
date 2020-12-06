#include "Sim800l.h"

Sim800l::Sim800l(uint8_t rx, uint8_t tx) :  SoftwareSerial(rx, tx) {

}

uint8_t Sim800l::checkDevice(void) {
  if (_lock) return Sim800l::BUSY;
  print("AT\r\n");
  return waitForResult();
}
uint8_t Sim800l::checkNetwork(uint8_t *type, uint8_t *status){
  if (_lock) return Sim800l::BUSY;
  print("AT+CREG?\r\n");
  uint8_t result = waitForResult();
  *type = _resultInt[0];
  *status = _resultInt[1];

  return result;
}
uint8_t Sim800l::checkSignal(uint8_t *strength, uint8_t *beacon) {
  if (_lock) return Sim800l::BUSY;
  print("AT+CSQ\r\n");
  uint8_t result = waitForResult();
  *strength = _resultInt[0];
  *beacon = _resultInt[1];

  return result;
}
uint8_t Sim800l::checkSim(void) {
  if (_lock) return Sim800l::BUSY;
  print("AT+CPIN?\r\n");
  return waitForResult();
}

uint8_t Sim800l::waitForResult(){
  return waitForResult(_timeout);
}

uint8_t Sim800l::waitForResult(uint32_t timeout){
  bool isData = false;
  uint32_t counter = 0;
  String buffer;

  while(!available()) {
    counter++; delay(1);
    if (counter == timeout) return Sim800l::TIMEOUT;
  }

  while(available()) {
    buffer += (char) read();
    counter++; delay(1);
    if (counter == timeout) return Sim800l::TIMEOUT;
  }

  uint8_t markA = buffer.indexOf(":");
  for (uint8_t index = 0; index < 5; index++){
    uint8_t markB = buffer.indexOf(",", markA + 1);
    
    String data;
    if (markB > 1) data = buffer.substring(markA + 1, markB); 
    else data = buffer.substring(markA + 1);

    _resultInt[index] = data.toInt();
    markA = markB;

    //Serial.println(data);
  }

  if (buffer.indexOf("OK") > -1) return Sim800l::OK;
  else if (buffer.indexOf("READY") > -1) return Sim800l::OK;
  else if (buffer.indexOf("ERROR") > -1) return Sim800l::ERROR;
  else return Sim800l::ERROR;
}

uint8_t Sim800l::sendSms(String number, String message){
  //lock sim800l
  _lock = true;
  //Serial.println("*gsm set to text mode");
  print("AT+CMGF=1\r\n");
  delay(200);
  
  //set sms command with number;
  print("AT+CMGS=\"" + number + "\"\r\n");
  delay(200);

  //set text message
  print(message);
  //set terminator
  write(26);
  //end
  print("\r\n");
  //unlock sim800l
  _lock = false;
  return waitForResult();
}