#include "Helper.h"
#include "Arduino.h"

String Helper::toUtf8Currency(uint32_t value) {
    memset(this->_buffer, 0, sizeof(this->_buffer));

    sprintf(this->_buffer, "%d.00", value);
    return String(this->_buffer);
}

String Helper::toUtf8Time(uint32_t value) {
    memset(this->_buffer, 0, sizeof(this->_buffer));

    uint8_t s = value % 60;
    uint8_t m = value / 60 % 60;
    uint8_t h = value / 3600;

    sprintf(this->_buffer, "%02d:%02d:%02d", h,m,s);
    return String(this->_buffer);
}

String Helper::padding(String data, String character, uint8_t length){
    for(uint8_t index = data.length(); index < length; index++){
        data += character;
    }
    return data;
}


String Helper::toHexString(uint8_t * data, uint8_t length){
    String str1 = "";

    for (uint8_t index = 0; index < length; index++) {
       char buff[4];
       sprintf(buff, "%02x", data[index]);
       str1 += String(buff);
    }
    
    return str1;
}

uint32_t Helper::parseInt(String value) {
    String buffer = "";

    for (uint8_t index = 0; index < value.length(); index++) {
        if (isDigit(value.charAt(index))) { 
            buffer += value.charAt(index); 
        }
    }
    
    return buffer.toInt();
}