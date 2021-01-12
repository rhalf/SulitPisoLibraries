#include "Device.h"
#include "Arduino.h"

static const uint8_t Device::LOGO[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x81, 0x00, 0x00, 0x00, 0x70, 0x00, 
  0x80, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFF, 0x01, 0xFE, 0x8F, 0x00, 
  0x00, 0x00, 0x70, 0x00, 0x00, 0xFC, 0xFF, 0x3F, 0xC0, 0xFF, 0xFF, 0xFF, 
  0x01, 0x0F, 0xFE, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0xF8, 0x03, 0x7F, 
  0xC0, 0x07, 0x7F, 0xF0, 0x81, 0x07, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0x00, 
  0x00, 0xF8, 0x03, 0xFE, 0xC0, 0x01, 0x7F, 0xC0, 0xC1, 0x03, 0xF0, 0x00, 
  0x00, 0x00, 0xFC, 0x00, 0x00, 0xF8, 0x03, 0xFC, 0xC1, 0x00, 0x7F, 0x80, 
  0xC1, 0x03, 0xE0, 0x00, 0x00, 0x00, 0xFC, 0x01, 0x00, 0xF8, 0x03, 0xF8, 
  0xC3, 0x00, 0x7F, 0x80, 0xE1, 0x03, 0xC0, 0x00, 0x00, 0x00, 0xFC, 0x01, 
  0x00, 0xF8, 0x03, 0xF8, 0x43, 0x00, 0x7F, 0x00, 0xE1, 0x03, 0xC0, 0x00, 
  0x00, 0x00, 0xFE, 0x01, 0x00, 0xF8, 0x03, 0xF8, 0x43, 0x00, 0x7F, 0x00, 
  0xE1, 0x07, 0x80, 0x00, 0x00, 0x00, 0xFE, 0x03, 0x00, 0xF8, 0x03, 0xF8, 
  0x03, 0x00, 0x7F, 0x00, 0xE0, 0x0F, 0x80, 0x00, 0x00, 0x00, 0xFB, 0x03, 
  0x00, 0xF8, 0x03, 0xF8, 0x03, 0x00, 0x7F, 0x00, 0xE0, 0x1F, 0x00, 0x00, 
  0x00, 0x00, 0xFB, 0x07, 0x00, 0xF8, 0x03, 0xF8, 0x03, 0x00, 0x7F, 0x00, 
  0xE0, 0x7F, 0x00, 0x00, 0x00, 0x80, 0xF1, 0x07, 0x00, 0xF8, 0x03, 0xF8, 
  0x01, 0x00, 0x7F, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x80, 0xF1, 0x0F, 
  0x00, 0xF8, 0x03, 0xFC, 0x01, 0x00, 0x7F, 0x00, 0xC0, 0xFF, 0x07, 0x00, 
  0x00, 0x80, 0xF0, 0x0F, 0x00, 0xF8, 0x03, 0xFE, 0x00, 0x00, 0x7F, 0x00, 
  0x80, 0xFF, 0x0F, 0x00, 0x00, 0xC0, 0xE0, 0x0F, 0x00, 0xF8, 0x03, 0x7F, 
  0x00, 0x00, 0x7F, 0x00, 0x00, 0xFF, 0x3F, 0x00, 0x00, 0xC0, 0xE0, 0x1F, 
  0x00, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xFE, 0x7F, 0x00, 
  0x00, 0x60, 0xC0, 0x1F, 0x00, 0xF8, 0xFF, 0x0F, 0x00, 0x00, 0x7F, 0x00, 
  0x00, 0xFC, 0xFF, 0x00, 0x00, 0x60, 0xC0, 0x3F, 0x00, 0xF8, 0xF3, 0x1F, 
  0x00, 0x00, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0x01, 0x00, 0x30, 0x80, 0x3F, 
  0x00, 0xF8, 0xE3, 0x1F, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xC0, 0xFF, 0x01, 
  0x00, 0xF0, 0xFF, 0x3F, 0x00, 0xF8, 0xC3, 0x3F, 0x00, 0x00, 0x7F, 0x00, 
  0x00, 0x00, 0xFF, 0x03, 0x00, 0xF8, 0xFF, 0x7F, 0x00, 0xF8, 0xC3, 0x7F, 
  0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x18, 0x00, 0x7F, 
  0x00, 0xF8, 0x83, 0x7F, 0x00, 0x00, 0x7F, 0x00, 0x20, 0x00, 0xF8, 0x03, 
  0x00, 0x18, 0x00, 0xFF, 0x00, 0xF8, 0x03, 0xFF, 0x00, 0x00, 0x7F, 0x00, 
  0x20, 0x00, 0xF0, 0x03, 0x00, 0x0C, 0x00, 0xFE, 0x00, 0xF8, 0x03, 0xFF, 
  0x01, 0x00, 0x7F, 0x00, 0x60, 0x00, 0xE0, 0x03, 0x00, 0x0C, 0x00, 0xFE, 
  0x01, 0xF8, 0x03, 0xFE, 0x01, 0x00, 0x7F, 0x00, 0x60, 0x00, 0xE0, 0x03, 
  0x00, 0x06, 0x00, 0xFE, 0x01, 0xF8, 0x03, 0xFC, 0x03, 0x00, 0x7F, 0x00, 
  0xE0, 0x00, 0xE0, 0x01, 0x00, 0x06, 0x00, 0xFC, 0x01, 0xF8, 0x03, 0xFC, 
  0x07, 0x00, 0x7F, 0x00, 0xE0, 0x01, 0xE0, 0x01, 0x00, 0x07, 0x00, 0xFC, 
  0x03, 0xF8, 0x03, 0xF8, 0x07, 0x00, 0x7F, 0x00, 0xE0, 0x03, 0xF0, 0x00, 
  0x00, 0x07, 0x00, 0xFC, 0x03, 0xF8, 0x03, 0xF0, 0x0F, 0x00, 0x7F, 0x00, 
  0xE0, 0x07, 0xF0, 0x00, 0x80, 0x0F, 0x00, 0xFC, 0x07, 0xFC, 0x07, 0xF0, 
  0x1F, 0x80, 0xFF, 0x00, 0xE0, 0x1F, 0x7C, 0x00, 0xE0, 0x7F, 0x80, 0xFF, 
  0x9F, 0xFF, 0x3F, 0xE0, 0x7F, 0xF0, 0xFF, 0x07, 0x60, 0xFC, 0x1F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x20, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x81, 0x73, 0xE0, 0xC1, 0x03, 0x3C, 0xF0, 
  0x81, 0x0F, 0x78, 0x70, 0x07, 0x7E, 0x80, 0x03, 0x60, 0x03, 0x33, 0xC0, 
  0x80, 0x01, 0x18, 0x60, 0x03, 0x1B, 0x30, 0x60, 0x02, 0x4C, 0xC0, 0x02, 
  0x60, 0x03, 0x33, 0xC0, 0x80, 0x01, 0x18, 0x60, 0x03, 0x1B, 0x30, 0xE0, 
  0x02, 0x2C, 0xC0, 0x00, 0xE0, 0x01, 0x3F, 0xC0, 0x80, 0x01, 0x18, 0xE0, 
  0x01, 0x0F, 0x30, 0xA0, 0x02, 0x3C, 0x80, 0x01, 0x60, 0x00, 0x33, 0xC0, 
  0x80, 0x01, 0x18, 0x60, 0x00, 0x03, 0x30, 0xA0, 0x03, 0x2C, 0x00, 0x03, 
  0x60, 0x00, 0x33, 0xC0, 0x80, 0x09, 0x18, 0x60, 0x00, 0x03, 0x30, 0x20, 
  0x03, 0x4C, 0x40, 0x03, 0xF0, 0x80, 0x73, 0xE0, 0xC1, 0x0F, 0x3C, 0xF0, 
  0x80, 0x07, 0x78, 0x70, 0x03, 0x7E, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x05, 0xCF, 0x81, 0x07, 0xC0, 0x83, 0x7F, 0x00, 0xF0, 0x07, 0x78, 
  0xC0, 0x05, 0xF8, 0x00, 0x60, 0x06, 0x86, 0x00, 0x03, 0x80, 0x81, 0x4C, 
  0x00, 0x60, 0x0C, 0x30, 0x60, 0x06, 0x8C, 0x01, 0x60, 0x04, 0x86, 0x00, 
  0x03, 0x80, 0x01, 0x0C, 0x00, 0x60, 0x0C, 0x30, 0x60, 0x04, 0x06, 0x03, 
  0xE0, 0x00, 0x86, 0x00, 0x03, 0x80, 0x01, 0x0C, 0x00, 0x60, 0x0C, 0x30, 
  0xE0, 0x00, 0x06, 0x03, 0xC0, 0x01, 0x86, 0x00, 0x03, 0x80, 0x01, 0x0C, 
  0x00, 0x60, 0x0C, 0x30, 0xC0, 0x01, 0x06, 0x03, 0x80, 0x03, 0x86, 0x00, 
  0x03, 0x80, 0x01, 0x0C, 0x00, 0xE0, 0x07, 0x30, 0x80, 0x03, 0x06, 0x03, 
  0x00, 0x07, 0x86, 0x00, 0x43, 0x80, 0x01, 0x0C, 0x00, 0x60, 0x00, 0x30, 
  0x00, 0x07, 0x06, 0x03, 0x20, 0x06, 0x86, 0x00, 0x43, 0x80, 0x01, 0x0C, 
  0x00, 0x60, 0x00, 0x30, 0x20, 0x06, 0x06, 0x03, 0x60, 0x06, 0x86, 0x00, 
  0x63, 0x80, 0x01, 0x0C, 0x00, 0x60, 0x00, 0x30, 0x60, 0x06, 0x8C, 0x01, 
  0xA0, 0x03, 0x7C, 0x80, 0x7F, 0xC0, 0x03, 0x1E, 0x00, 0xF0, 0x00, 0x78, 
  0xA0, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00 };



static const char  Device::COMPANY[] PROGMEM            = "A.R.T.S";
static const char  Device::COUNTRY[] PROGMEM            = "Philippines";

static const char  Device::TERMINAL[] PROGMEM           = "Terminal";
static const char  Device::COIN[] PROGMEM               = "Coin";
static const char  Device::VACANT[] PROGMEM             = "Vacant";
static const char  Device::TIME[] PROGMEM               = "Time";
static const char  Device::FREE[] PROGMEM               = "Free";
static const char  Device::LIMIT[] PROGMEM              = "Limit";

static const char  Device::TRANSACTION[] PROGMEM        = "Trans";
static const char  Device::AMOUNT[] PROGMEM             = "Amount";
static const char  Device::CREDIT[] PROGMEM             = "Credit";
static const char  Device::SERVE[] PROGMEM              = "Serve";
static const char  Device::POWER[] PROGMEM              = "Power";

static const char * const Device::TABLE[] PROGMEM= { 
    Device::COMPANY, 
    Device::COUNTRY, 

    Device::TERMINAL,
    Device::COIN,
    Device::VACANT,
    Device::TIME,
    Device::FREE,
    Device::LIMIT,

    Device::TRANSACTION,
    Device::AMOUNT,
    Device::CREDIT,
    Device::SERVE,
    Device::POWER
};

static char Device::buffer[12];

static char * Device::getCompany() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[0]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}
static char * Device::getCountry() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[1]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getTerminal() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[2]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getCoin() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[3]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getVacant() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[4]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getTime() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[5]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getFree() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[6]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getLimit() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[7]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getTrans() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[8]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getAmount() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[9]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getCredit() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[10]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

static char * Device::getServe() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[11]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}


static char * Device::getPower() {
    char * ptr = (char *) pgm_read_word(&Device::TABLE[12]);
    strcpy_P(Device::buffer, ptr);
    return  Device::buffer;
}

