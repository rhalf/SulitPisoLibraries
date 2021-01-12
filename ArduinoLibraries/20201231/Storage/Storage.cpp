#include "Storage.h"
#include "Arduino.h"
#include "EEPROM.h"

//=============================================================================
void Storage::setFirst(uint32_t first){
   EEPROM.put(Storage::FIRST, first); 
}
uint32_t Storage::getFirst(void){
   uint32_t first; 
   EEPROM.get(Storage::FIRST, first);
   return first;
}
//=============================================================================
void Storage::setFirmware(uint32_t firmware){
   EEPROM.put(Storage::FIRMWARE, firmware); 
}
uint32_t Storage::getFirmware(void){
   uint32_t firmware; 
   EEPROM.get(Storage::FIRMWARE, firmware);
   return firmware;
}
//=============================================================================
void Storage::setMode(uint32_t mode){
   EEPROM.put(Storage::MODE, mode); 
}
uint32_t Storage::getMode(void){
   uint32_t mode; 
   EEPROM.get(Storage::MODE, mode);
   return mode;
}
//=============================================================================
void Storage::clear(uint32_t date) { 
   EEPROM.put(Storage::CURRENT_TRANSA, _zero);
   EEPROM.put(Storage::CURRENT_AMOUNT, _zero);
   EEPROM.put(Storage::CURRENT_TRANSC, _zero);
   EEPROM.put(Storage::CURRENT_CREDIT, _zero);
   EEPROM.put(Storage::CURRENT_TRANSF, _zero);
   EEPROM.put(Storage::CURRENT_FREE, _zero);

   EEPROM.put(Storage::CURRENT_SERVE, _zero);
   EEPROM.put(Storage::CURRENT_TIME, _zero);
   EEPROM.put(Storage::CURRENT_POWER, _zero);

   EEPROM.put(Storage::CLEAR, date); 
}
uint32_t Storage::getClearDate(void) {
   uint32_t date; 
   EEPROM.get(Storage::CLEAR, date);
   return date;
}
//=============================================================================
void Storage::reset(uint32_t date) {
   EEPROM.put(Storage::MODE, _zero); 
   EEPROM.put(Storage::PIN, _pin); 
   EEPROM.put(Storage::RATE, _rate); 
   EEPROM.put(Storage::MINIMUM, _zero);
   EEPROM.put(Storage::LIMIT, _limit);
   EEPROM.put(Storage::PKWH, _pkwh);

   EEPROM.put(Storage::RESET, date);
}
uint32_t Storage::getResetDate(void) {
   uint32_t date; 
   EEPROM.get(Storage::RESET, date);
   return date;
}
//=============================================================================
void Storage::format(uint32_t date) {
   EEPROM.put(Storage::MODE, _zero); 
   EEPROM.put(Storage::PIN, _pin); 
   EEPROM.put(Storage::RATE, _rate); 
   EEPROM.put(Storage::MINIMUM, _zero);
   EEPROM.put(Storage::LIMIT, _limit);
   EEPROM.put(Storage::PKWH, _pkwh);

   EEPROM.put(Storage::CURRENT_TRANSA, _zero);
   EEPROM.put(Storage::CURRENT_AMOUNT, _zero);
   EEPROM.put(Storage::CURRENT_TRANSC, _zero);
   EEPROM.put(Storage::CURRENT_CREDIT, _zero);
   EEPROM.put(Storage::CURRENT_TRANSF, _zero);
   EEPROM.put(Storage::CURRENT_FREE, _zero);

   EEPROM.put(Storage::CURRENT_SERVE, _zero);
   EEPROM.put(Storage::CURRENT_TIME, _zero);
   EEPROM.put(Storage::CURRENT_POWER, _zero);

   EEPROM.put(Storage::LIFETIME_TRANSA, _zero);
   EEPROM.put(Storage::LIFETIME_AMOUNT, _zero);
   EEPROM.put(Storage::LIFETIME_TRANSC, _zero);
   EEPROM.put(Storage::LIFETIME_CREDIT, _zero);
   EEPROM.put(Storage::LIFETIME_TRANSF, _zero);
   EEPROM.put(Storage::LIFETIME_FREE, _zero);

   EEPROM.put(Storage::LIFETIME_SERVE, _zero);
   EEPROM.put(Storage::LIFETIME_TIME, _zero);
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
//=============================================================================
void Storage::setPin(uint32_t pin) { 
   EEPROM.put(Storage::PIN, pin); 
}
uint32_t Storage::getPin(void) {
   uint32_t pin; 
   EEPROM.get(Storage::PIN, pin);
   return pin;
}
//=============================================================================
void Storage::setRate(uint32_t rate) { 
   EEPROM.put(Storage::RATE, rate); 
}
uint32_t Storage::getRate(void) {
   uint32_t rate; 
   EEPROM.get(Storage::RATE, rate);
   return rate;
}
//=============================================================================
void Storage::setMinimum(uint32_t min) { 
   EEPROM.put(Storage::MINIMUM, min); 
}
uint32_t Storage::getMinimum(void) {
   uint32_t min; 
   EEPROM.get(Storage::MINIMUM, min);
   return min;
}
//=============================================================================
void Storage::setLimit(uint32_t lim) { 
   EEPROM.put(Storage::LIMIT, lim); 
}
uint32_t Storage::getLimit(void) {
   uint32_t lim; 
   EEPROM.get(Storage::LIMIT, lim);
   return lim;
}
//=============================================================================
void Storage::setPkwh(uint32_t pkwh) {
   EEPROM.put(Storage::PKWH, pkwh); 
}
uint32_t Storage::getPkwh(void) {
   uint32_t pkwh; 
   EEPROM.get(Storage::PKWH, pkwh);
   return pkwh;
}
//=============================================================================
void Storage::incrementTransA(uint16_t value) {
   uint32_t transA; 
   //store to current
   EEPROM.get(Storage::CURRENT_TRANSA, transA);
   transA += value;
   EEPROM.put(Storage::CURRENT_TRANSA, transA);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_TRANSA, transA);
   transA += value;
   EEPROM.put(Storage::LIFETIME_TRANSA, transA);
}
uint32_t Storage::getCurrentTransA(void) { 
   uint32_t transA; 
   EEPROM.get(Storage::CURRENT_TRANSA, transA);
   return transA;
}
uint32_t Storage::getLifetimeTransA (void) {
   uint32_t transA; 
   EEPROM.get(Storage::LIFETIME_TRANSA, transA);
   return transA;
}
//=============================================================================
void Storage::incrementAmount(uint16_t value) {
   uint32_t amount; 
   //store to current
   EEPROM.get(Storage::CURRENT_AMOUNT, amount);
   amount += value;
   EEPROM.put(Storage::CURRENT_AMOUNT, amount);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_AMOUNT, amount);
   amount += value;
   EEPROM.put(Storage::LIFETIME_AMOUNT, amount);

   Storage::incrementTransA(1);
   Storage::incrementServe(value * Storage::getRate());
}
uint32_t Storage::getCurrentAmount(void) { 
   uint32_t amount; 
   EEPROM.get(Storage::CURRENT_AMOUNT, amount);
   return amount;
}
uint32_t Storage::getLifetimeAmount (void) {
   uint32_t amount; 
   EEPROM.get(Storage::LIFETIME_AMOUNT, amount);
   return amount;
}
//=============================================================================
void Storage::incrementTransC(uint16_t value) {
   uint32_t transC; 
   //store to current
   EEPROM.get(Storage::CURRENT_TRANSC, transC);
   transC += value;
   EEPROM.put(Storage::CURRENT_TRANSC, transC);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_TRANSC, transC);
   transC += value;
   EEPROM.put(Storage::LIFETIME_TRANSC, transC);
}
uint32_t Storage::getCurrentTransC(void) { 
   uint32_t transC; 
   EEPROM.get(Storage::CURRENT_TRANSC, transC);
   return transC;
}
uint32_t Storage::getLifetimeTransC (void) {
   uint32_t transC; 
   EEPROM.get(Storage::LIFETIME_TRANSC, transC);
   return transC;
}
//=============================================================================
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
   Storage::incrementTransC(1);
   Storage::incrementServe(value * Storage::getRate());
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
void Storage::incrementTransF(uint16_t value) {
   uint32_t transF; 
   //store to current
   EEPROM.get(Storage::CURRENT_TRANSF, transF);
   transF += value;
   EEPROM.put(Storage::CURRENT_TRANSF, transF);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_TRANSF, transF);
   transF += value;
   EEPROM.put(Storage::LIFETIME_TRANSF, transF);
}
uint32_t Storage::getCurrentTransF(void) { 
   uint32_t transF; 
   EEPROM.get(Storage::CURRENT_TRANSF, transF);
   return transF;
}
uint32_t Storage::getLifetimeTransF (void) {
   uint32_t transF; 
   EEPROM.get(Storage::LIFETIME_TRANSF, transF);
   return transF;
}
//=============================================================================
void Storage::incrementFree(uint16_t value) {
   uint32_t free; 
   //store to current
   EEPROM.get(Storage::CURRENT_FREE, free);
   free += value;
   EEPROM.put(Storage::CURRENT_FREE, free);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_FREE, free);
   free += value;
   EEPROM.put(Storage::LIFETIME_FREE, free);
   Storage::incrementTransF(1);
   Storage::incrementServe(value * Storage::getRate());
}
uint32_t Storage::getCurrentFree(void) { 
   uint32_t free; 
   EEPROM.get(Storage::CURRENT_FREE, free);
   return free;
}
uint32_t Storage::getLifetimeFree(void) {
   uint32_t free; 
   EEPROM.get(Storage::LIFETIME_FREE, free);
   return free;
}
//=============================================================================
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
//=============================================================================
void Storage::incrementTime(uint16_t value) {
   uint32_t time; 
   //store to current
   EEPROM.get(Storage::CURRENT_TIME, time);
   time += value;
   EEPROM.put(Storage::CURRENT_TIME, time);
   //store to lifetime
   EEPROM.get(Storage::LIFETIME_TIME, time);
   time += value;
   EEPROM.put(Storage::LIFETIME_TIME, time);
}
uint32_t Storage::getCurrentTime(void) { 
   uint32_t time; 
   EEPROM.get(Storage::CURRENT_TIME, time);
   return time;
}
uint32_t Storage::getLifetimeTime(void) {
   uint32_t time; 
   EEPROM.get(Storage::LIFETIME_TIME, time);
   return time;
}

