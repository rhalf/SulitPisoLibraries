#include "Storage.h"
#include "Arduino.h"
#include "EEPROM.h"


Storage::Storage(void) {

}
//first
void Storage::setFirst(uint32_t first){
   EEPROM.put(Storage::FIRST, first); 
}
uint32_t Storage::getFirst(void){
   uint32_t first; 
   EEPROM.get(Storage::FIRST, first);
   return first;
}

//firmware
void Storage::setFirmware(uint32_t firmware){
   EEPROM.put(Storage::FIRMWARE, firmware); 
}
uint32_t Storage::getFirmware(void){
   uint32_t firmware; 
   EEPROM.get(Storage::FIRMWARE, firmware);
   return firmware;
}

//mode
void Storage::setMode(uint32_t mode){
   EEPROM.put(Storage::MODE, mode); 
}
uint32_t Storage::getMode(void){
   uint32_t mode; 
   EEPROM.get(Storage::MODE, mode);
   return mode;
}

//Clear
void Storage::clear(uint32_t date) { 
   EEPROM.put(Storage::CURRENT_TRANSACT, _zero);
   EEPROM.put(Storage::CURRENT_GROSS, _zero);
   EEPROM.put(Storage::CURRENT_SERVE, _zero);
   EEPROM.put(Storage::CURRENT_CREDIT, _zero);
   EEPROM.put(Storage::CURRENT_POWER, _zero);
   
   EEPROM.put(Storage::CLEAR, date); 
}
uint32_t Storage::getClearDate(void) {
   uint32_t date; 
   EEPROM.get(Storage::CLEAR, date);
   return date;
}
//reset
void Storage::reset(uint32_t date) {
   EEPROM.put(Storage::MODE, _zero); 
   EEPROM.put(Storage::PIN, _pin); 
   EEPROM.put(Storage::RATE, _rate); 
   EEPROM.put(Storage::MINIMUM, _zero);
   EEPROM.put(Storage::LIMIT, _limit);

   EEPROM.put(Storage::RESET, date);
}
uint32_t Storage::getResetDate(void) {
   uint32_t date; 
   EEPROM.get(Storage::RESET, date);
   return date;
}
//format
void Storage::format(uint32_t date) {
   EEPROM.put(Storage::MODE, _zero); 
   EEPROM.put(Storage::PIN, _pin); 
   EEPROM.put(Storage::RATE, _rate); 
   EEPROM.put(Storage::MINIMUM, _zero);
   EEPROM.put(Storage::LIMIT, _limit);

   EEPROM.put(Storage::CURRENT_TRANSACT, _zero);
   EEPROM.put(Storage::CURRENT_GROSS, _zero);
   EEPROM.put(Storage::CURRENT_SERVE, _zero);
   EEPROM.put(Storage::CURRENT_CREDIT, _zero);
   EEPROM.put(Storage::CURRENT_POWER, _zero);

   EEPROM.put(Storage::LIFETIME_TRANSACT, _zero);
   EEPROM.put(Storage::LIFETIME_GROSS, _zero);
   EEPROM.put(Storage::LIFETIME_SERVE, _zero);
   EEPROM.put(Storage::LIFETIME_CREDIT, _zero);
   EEPROM.put(Storage::LIFETIME_POWER, _zero);

   EEPROM.put(Storage::CLEAR, date);
   EEPROM.put(Storage::RESET, date);
   EEPROM.put(Storage::FORMAT, date);
}
uint32_t Storage::getFormatDate(void) {
   uint32_t date; 
   EEPROM.get(Storage::FORMAT, date);
   return date;
}
//Pin
void Storage::setPin(uint32_t pin) { 
   EEPROM.put(Storage::PIN, pin); 
}
uint32_t Storage::getPin(void) {
   uint32_t pin; 
   EEPROM.get(Storage::PIN, pin);
   return pin;
}
//Rate
void Storage::setRate(uint32_t rate) { 
   EEPROM.put(Storage::RATE, rate); 
}
uint32_t Storage::getRate(void) {
   uint32_t rate; 
   EEPROM.get(Storage::RATE, rate);
   return rate;
}
//Minimum
void Storage::setMinimum(uint32_t min) { 
   EEPROM.put(Storage::MINIMUM, min); 
}
uint32_t Storage::getMinimum(void) {
   uint32_t min; 
   EEPROM.get(Storage::MINIMUM, min);
   return min;
}
//Limit
void Storage::setLimit(uint32_t lim) { 
   EEPROM.put(Storage::LIMIT, lim); 
}
uint32_t Storage::getLimit(void) {
   uint32_t lim; 
   EEPROM.get(Storage::LIMIT, lim);
   return lim;
}
//=============================================================================
//Transaction
void Storage::incrementTransaction(uint16_t value) {
   uint32_t transaction; 
   //store to current
   EEPROM.get(Storage::CURRENT_TRANSACT, transaction);
   transaction += value;
   EEPROM.put(Storage::CURRENT_TRANSACT, transaction);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_TRANSACT, transaction);
   transaction += value;
   EEPROM.put(Storage::LIFETIME_TRANSACT, transaction);
}
uint32_t Storage::getCurrentTransaction(void) { 
   uint32_t transaction; 
   EEPROM.get(Storage::CURRENT_TRANSACT, transaction);
   return transaction;
}
uint32_t Storage::getLifetimeTransaction (void) {
   uint32_t transaction; 
   EEPROM.get(Storage::LIFETIME_TRANSACT, transaction);
   return transaction;
}
//Gross
void Storage::incrementGross(uint16_t value) {
   uint32_t gross; 
   //store to current
   EEPROM.get(Storage::CURRENT_GROSS, gross);
   gross += value;
   EEPROM.put(Storage::CURRENT_GROSS, gross);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_GROSS, gross);
   gross += value;
   EEPROM.put(Storage::LIFETIME_GROSS, gross);
}
uint32_t Storage::getCurrentGross(void) { 
   uint32_t gross; 
   EEPROM.get(Storage::CURRENT_GROSS, gross);
   return gross;
}
uint32_t Storage::getLifetimeGross (void) {
   uint32_t gross; 
   EEPROM.get(Storage::LIFETIME_GROSS, gross);
   return gross;
}
//=============================================================================
//Serve
void Storage::incrementServe(uint16_t value) {
   uint32_t serve; 
   //store to current
   EEPROM.get(Storage::CURRENT_SERVE, serve);
   serve += value;
   EEPROM.put(Storage::CURRENT_SERVE, serve);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_SERVE, serve);
   serve += value;
   EEPROM.put(Storage::LIFETIME_SERVE, serve);
}
uint32_t Storage::getCurrentServe(void) { 
   uint32_t serve; 
   EEPROM.get(Storage::CURRENT_SERVE, serve);
   return serve;
}
uint32_t Storage::getLifetimeServe(void) {
   uint32_t serve; 
   EEPROM.get(Storage::LIFETIME_SERVE, serve);
   return serve;
}

//=============================================================================
//Credit
void Storage::incrementCredit(uint16_t value) {
   uint32_t credit; 
   //store to current
   EEPROM.get(Storage::CURRENT_CREDIT, credit);
   credit += value;
   EEPROM.put(Storage::CURRENT_CREDIT, credit);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_CREDIT, credit);
   credit += value;
   EEPROM.put(Storage::LIFETIME_CREDIT, credit);
}
uint32_t Storage::getCurrentCredit(void) { 
   uint32_t credit; 
   EEPROM.get(Storage::CURRENT_CREDIT, credit);
   return credit;
}
uint32_t Storage::getLifetimeCredit(void) {
   uint32_t credit; 
   EEPROM.get(Storage::LIFETIME_CREDIT, credit);
   return credit;
}

//=============================================================================
//power
void Storage::incrementPower(uint16_t value) {
   uint32_t power; 
   //store to current
   EEPROM.get(Storage::CURRENT_POWER, power);
   power += value;
   EEPROM.put(Storage::CURRENT_POWER, power);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_POWER, power);
   power += value;
   EEPROM.put(Storage::LIFETIME_POWER, power);
}
uint32_t Storage::getCurrentPower(void) { 
   uint32_t power; 
   EEPROM.get(Storage::CURRENT_POWER, power);
   return power;
}
uint32_t Storage::getLifetimePower(void) {
   uint32_t power; 
   EEPROM.get(Storage::LIFETIME_POWER, power);
   return power;
}

