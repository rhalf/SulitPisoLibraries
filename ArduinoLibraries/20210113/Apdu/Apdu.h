#ifndef _APDU_H
#define _APDU_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
//typedef void (* CallBack)();

class Apdu {

public:

  Apdu();
  Apdu(byte * data);

  uint8_t cClass = 0;
  uint8_t cFunc = 0;
  uint8_t cParam = 0;
  uint8_t cState = 0;

  uint32_t cValue1 = 0;
  uint32_t cValue2 = 0;

  uint8_t cCheckSum = 0;

  uint8_t cRaw[13];

  void parse(byte * data);
  void generate();
  String toString();
  void clear();
  uint8_t checkSum();


  static const uint8_t SIZE = 13;
  static void intToBe(byte * data, uint32_t value);
  static uint32_t beToInt(byte * data);
  static uint32_t swapByte( uint32_t value);


private:

};
#endif // _APDU_H
