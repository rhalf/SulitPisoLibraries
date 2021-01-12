#ifndef _DEVICE_H
#define _DEVICE_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>

// logo : byte arry 128x64 | 8192 pixels

class Device {

   public:
      static const uint8_t LOGO[] PROGMEM;

      static char * getCompany();
      static char * getCountry();
 
      static char * getTerminal();
      static char * getCoin();
      static char * getVacant();
      static char * getTime();
      static char * getFree();

      static char * getTrans();
      static char * getAmount();
      static char * getServe();
      static char * getCredit();
      static char * getPower();
      static char * getLimit();

   private:
      static const char  COMPANY[] PROGMEM;
      static const char  COUNTRY[] PROGMEM;

      static const char  TERMINAL[] PROGMEM;
      static const char  COIN[] PROGMEM;
      static const char  VACANT[] PROGMEM;
      static const char  TIME[] PROGMEM;
      static const char  FREE[] PROGMEM;

      static const char  TRANSACTION[] PROGMEM;
      static const char  AMOUNT[] PROGMEM;
      static const char  SERVE[] PROGMEM;
      static const char  CREDIT[] PROGMEM;
      static const char  POWER[] PROGMEM;
      static const char  LIMIT[] PROGMEM;

      static const char * const TABLE[] PROGMEM;
      static char buffer[12];
};


#endif // _DEVICE_H
