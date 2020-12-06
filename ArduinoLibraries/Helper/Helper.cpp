#include "Helper.h"
#include "Arduino.h"

String Helper::toUtf8(float value) {
    memset(_buffer, 0, sizeof(_buffer));

    sprintf(_buffer, "%d", value);
    return String(_buffer);
}

String Helper::toUtf8Currency(uint32_t value) {
    memset(_buffer, 0, sizeof(_buffer));

    sprintf(_buffer, "%d.00", value);
    return String(_buffer);
}
String Helper::toUtf8Time(uint32_t value) {
    memset(_buffer, 0, sizeof(_buffer));

    uint8_t s = value % 60;
    uint8_t m = value / 60 % 60;
    uint8_t h = value / 3600;

    sprintf(_buffer, "%02d:%02d:%02d", h,m,s);
    return String(_buffer);
}
String Helper::toUtf8DateTime(uint32_t value) {
    memset(_buffer, 0, sizeof(_buffer));

    uint8_t s = value % 60;
    uint8_t m = value / 60 % 60;
    uint8_t h = value / 3600 % 24;
    
    uint8_t d = value / 3600 / 24 % 30;
    uint8_t M = value / 3600 / 24 / 30 % 12;
    uint8_t y = value / 3600 / 24 / 30 / 12;
    sprintf(_buffer, "%02d-%02d-%02d %02d:%02d:%02d", y,M,d,h,m,s);
    return String(_buffer);
}
String Helper::padding(String data, String character, uint8_t length){
    for(_index = data.length(); _index < length; _index++){
        data += character;
    }
    return data;
}
String Helper::toHexString(uint8_t * data, uint8_t length){
    String str1 = "";
    for (_index = 0; _index < length; _index++) {
       char buff[4];
       sprintf(buff, "%02x", data[_index]);
       str1 += String(buff);
    }
    return str1;
}
uint32_t Helper::parseInt(String value) {
    String buffer = "";
    for (_index = 0; _index < value.length(); _index++) {
        if (isDigit(value.charAt(_index))) { 
            buffer += value.charAt(_index); 
        }
    }
    return buffer.toInt();
}