#include "Timestamp.h"
#include "Arduino.h"
// typedef void (* CallBack)();

Timestamp::Timestamp(void) {
  _timestamp = 0;
  _gmt = 0;
  _value = _timestamp;
}

Timestamp::Timestamp(int32_t value, int32_t gmt){
  _gmt = gmt;
  _timestamp = value;
  _value = _timestamp + (gmt * 3600);
}
// Timestamp::Timestamp(char * value, int32_t gmt){
//   _gmt = gmt;

//   int32_t year = ((value[0] -'0') * 1000) + ((value[1] -'0') * 100) + ((value[2] -'0') * 10) + (value[3] -'0');
//   int32_t month = ((value[5] -'0') * 10) + (value[6] -'0');
//   int32_t day = ((value[8] -'0') * 10) + (value[9] -'0');
//   int32_t hour = ((value[11] -'0') * 10) + (value[12] -'0');
//   int32_t minute = ((value[14] -'0') * 10) + (value[15] -'0');
//   int32_t second = ((value[17] -'0') * 10) + (value[18] -'0');

//   _timestamp += (year - _year) *  31556926;
//   _timestamp += (month-1) * 2629743;
//   _timestamp += (day-1) * 86400;
//   _timestamp += hour * 3600;
//   _timestamp += minute * 60;
//   _timestamp += second;
//   _timestamp -= _excess;
//   _value = _timestamp + (gmt * 3600);
// }


//int32_t Timestamp::getSecond(void) { return (((((_value % 31556926) % 2629743) % 86400) % 3600) % 60) / 1; }
int32_t Timestamp::getSecond(void) { return _value % 60; }
int32_t Timestamp::getMinute(void) { return _value / 60 % 60; }
int32_t Timestamp::getHour(void) { return _value / 60 / 60  % 24; }
// int32_t Timestamp::getDay(void) { return _value / 60 / 60 / 24 % 30.44; }
// int32_t Timestamp::getMonth(void) { return _value / 60 / 60 / 24 % 365.24; }
int32_t Timestamp::getDay(void) { return (((_value % 31556926) % 2629743) / 86400) + 1; }
int32_t Timestamp::getMonth(void) { return ((_value % 31556926) / 2629743) + 1; }
int32_t Timestamp::getYear(void) { return (_value / 31556926) + _year; }


void Timestamp::setTimestamp(int32_t value, int32_t gmt){
  _gmt = gmt;
  _timestamp = value;
  _value = _timestamp + (gmt * 3600);
}

String Timestamp::toString(void) {
  String builder;
  builder += String(getYear());
  builder += String("-");

  if (getMonth() < 10) builder += "0";
  builder += String(getMonth());
  builder += String("-");
   if (getDay() < 10) builder += "0";
  builder += String(getDay());

  builder += String(" ");
 
  if (getHour() < 10) builder += "0";
  builder += String(getHour());
  builder += String(":");
  
  if (getMinute() < 10) builder += "0";
  builder += String(getMinute());
  builder += String(":");

  if (getSecond() < 10) builder += "0";
  builder += String(getSecond());
  return builder;
};


int32_t Timestamp::toInt32(void) {
  return _timestamp;
}
