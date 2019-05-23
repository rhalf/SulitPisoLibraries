#include "Protocol.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Storage.h"
#include "Helper.h"
#include "Timer.h"

typedef void (* Callback)();

Protocol::Protocol(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx) {
   _storage = Storage();
   _helper = Helper();

   buffer.reserve(128);
   timeOut = 2000;
}

void Protocol::interpret(void) {
   String device = "f" + String(_storage.getFirmware());
   String comma = ",";
   String ok = "OK";

   uint8_t index[3];
   index[0] = buffer.indexOf(comma);
   index[1] = buffer.indexOf(comma, index[0] + 1);
   index[2] = buffer.indexOf(comma, index[1] + 1);

   String pinCode = buffer.substring(0, index[0]);
   String command = buffer.substring(index[0] + 1, index[1]);
   String param1 = buffer.substring(index[1] + 1, index[2]);
   String param2 = buffer.substring(index[2] + 1);

   uint32_t pin = _helper.parseInt(pinCode);
   uint32_t value1 = _helper.parseInt(param1);
   uint32_t value2 = _helper.parseInt(param2);
   
   buffer = device + comma + command + comma;

   //========================================================================== Unauthorized Commands
   if (command == "FR") {
      // Format
      _storage.format(value1);
      buffer += ok;
      buffer += "\n"; 
      return;
   }

   if (command == "GA") {
      //2
      buffer +=  String(_storage.getMode()) + comma;
      //3,4,5
      buffer += String(_storage.getFormatDate()) + comma + String(_storage.getResetDate()) + comma  + String(_storage.getClearDate()) + comma;
      //6,7,8,9
      buffer += String(Timer::getSeconds()) + comma + String(_storage.getRate()) + comma + String(_storage.getMinimum()) + comma + String(_storage.getLimit()) + comma;
      //10,11,12,13
      buffer += String(terminals[0].timeLapse) + comma;
      buffer += String(terminals[1].timeLapse) + comma;
      buffer += String(terminals[2].timeLapse) + comma;
      buffer += String(terminals[3].timeLapse) + comma;
      //14,15 transaction
      buffer += String(_storage.getCurrentTransaction()) + comma + String(_storage.getLifetimeTransaction()) + comma;
      //16,17 gross
      buffer += String(_storage.getCurrentGross()) + comma +  String(_storage.getLifetimeGross()) + comma;
      //18,19 serve
      buffer += String(_storage.getCurrentServe()) + comma +  String(_storage.getLifetimeServe()) + comma;
      //20,21 credit
      buffer += String(_storage.getCurrentCredit()) + comma + String(_storage.getLifetimeCredit())+ comma;
      //22,23 power
      buffer += String(_storage.getCurrentPower()) + comma + String(_storage.getLifetimePower());
      buffer += "\n"; 
      return;
   }

   //========================================================================== Authorized Commands
   if (pin != _storage.getPin()) {
      // Wrong Pin
      buffer += "01";  
      buffer += "\n"; 
      return;
   }

   
   if (command == "MD") { 
      // mode
      _storage.setMode(value1);
      buffer += ok;
   } else if (command == "CT") { 
      // credit terminal
      uint16_t coinValue = value2;
      uint16_t timeValue = value2 * _storage.getRate();
      //add to record
      _storage.incrementCredit(coinValue);
      _storage.incrementServe(timeValue);
      terminals[value1].set(timeValue);

      buffer += ok;
   } else if (command == "PN") { 
      // set pin
      _storage.setPin(value1);
      buffer += ok;
   } else if (command == "RA") {
      // set rate
      _storage.setRate(value1);
      buffer += ok;
   } else if (command == "MI") { 
      // set minimum
      _storage.setMinimum(value1);
      buffer += ok;
   } else if (command == "LI") { 
      // set limit
      _storage.setLimit(value1);
      buffer += ok;
   } else if (command == "RT") {
      // reset
      _storage.reset(value1);
      buffer += ok;
   } else if (command == "CE") {
      // clear 
      _storage.clear(value1);
      buffer += ok;
   } else if (command == "RB") {
      // reboot
      while(true){}
   } else {
      buffer += "02"; //Wrong Command | Command Not Exist
   }

   buffer += "\n";
}

void Protocol::setOnReceived(Callback onReceived) {
   _onReceived = onReceived;
}

void Protocol::send() {
   print(buffer + "\n");
}

void Protocol::run (void){    
   if (available()) {
         if (available()) {
            char chr = (char) read();
            buffer += chr;
            if (chr == '\n') {
               _onReceived();
               buffer = "";
               return;
            }
         }
   }
}