#include "Apdu.h"
#include "Arduino.h"
// typedef void (* CallBack)();

  
Apdu::Apdu() {
  clear();
}

Apdu::Apdu(byte * data) {
 parse(data);
}

void Apdu::parse(byte * data) {
  cClass = data[0];
  cFunc = data[1];
  cParam = data[2];
  cState = data[3];
  cValue1 = beToInt(data + 4);
  cValue2 = beToInt(data + 8);
  memcpy(cRaw, data, SIZE);
  for (uint8_t index = 0; index < SIZE - 1; index++) cCheckSum += cRaw[index];
}

uint8_t Apdu::checkSum() {
  uint8_t cs = 0;
  for (uint8_t index = 0; index < SIZE - 1; index++) cs += cRaw[index];
  if (cs == cCheckSum) return 1;
  else return 0;
}

uint32_t Apdu::beToInt(byte * data) {
  return (uint32_t) data[0] << 24 | (uint32_t) data[1] << 16 | (uint32_t) data[2] << 8 | (uint32_t) data[3] << 0;
}

void Apdu::intToBe(byte * data, uint32_t value) {
  data[0] = (value >> 24) & 0xFF;  // highest byte
  data[1] = (value >> 16) & 0xFF;  // byte
  data[2] = (value >> 8) & 0xFF;   // byte
  data[3] = (value >> 0) & 0xFF;   // lowest byte
}

uint32_t  Apdu::swapByte( uint32_t value ) {
    value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF ); 
    return (value << 16) | ((value >> 16) & 0xFFFF);
}

void Apdu::generate() {
  cRaw[0] = cClass;
  cRaw[1] = cFunc;
  cRaw[2] = cParam;
  cRaw[3] = cState;
  intToBe(cRaw + 4, cValue1);
  intToBe(cRaw + 8, cValue2);
  for (uint8_t index = 0; index < SIZE - 1; index++) cRaw[12] += cRaw[index];
  cCheckSum = cRaw[12];
}

void Apdu::clear() {
  memset(cRaw, 0 , SIZE);
  cClass = 0;
  cFunc = 0;
  cParam = 0;
  cState = 0;
  cValue1 = 0;
  cValue2 = 0;
  cCheckSum = 0;
}

String Apdu::toString() {
  //d0,1,0,0,5f,e1,98,86,0,0,0,0,0,

  String builder;
  for (uint8_t index; index < SIZE; index++) {
    builder += String(cRaw[index], HEX);
    if (index != SIZE - 1) builder += ",";
  } 
  return builder;
}