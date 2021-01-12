#ifndef _TIMESTAMP_H
#define _TIMESTAMP_H

#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
//typedef void (* CallBack)();

class Timestamp {

public:

  Timestamp();
  Timestamp(int32_t value, int32_t gmt);
  // Timestamp(char * value, int32_t gmt);
  void setTimestamp(int32_t value, int32_t gmt);

  int32_t getSecond(void);
  int32_t getMinute(void);
  int32_t getHour(void);
  int32_t getDay(void);
  int32_t getMonth(void);
  int32_t getYear(void);
 




  String toString(void);
  int32_t toInt32(void);


private:
  int32_t _timestamp = 0;
  int32_t _value = 0;

  int32_t _year = 1970;
  int32_t _gmt = 0;
  // int32_t _excess = 21473;

};
#endif // _TIMESTAMP_H
