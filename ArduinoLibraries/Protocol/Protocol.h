#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Storage.h"
#include "Helper.h"
#include "Terminal.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (* Callback)();

class Protocol : public SoftwareSerial {
  
   public:

      void interpret(void);

      // uint8_t generateSum();
      // bool verifySum();

      String buffer;
      Terminal * terminals;
      uint32_t timeOut;

      Protocol(uint8_t rx, uint8_t tx);
      void setOnReceived(Callback onReceived);
      void run(void);
      void send();

   private:
      Callback _onReceived;
      uint8_t _index = 0;

      Storage _storage;
      Helper _helper;
};


#endif // _PROTOCOL_H
