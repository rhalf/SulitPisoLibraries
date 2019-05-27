#ifndef _STORAGE_H
#define _STORAGE_H

#include "Arduino.h"
#include "EEPROM.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>


class Storage {
    public:

        static const uint8_t OFFSET                = sizeof(uint32_t) + 0;
        
        static const uint8_t FIRST                 = OFFSET * 1;
        static const uint8_t FIRMWARE              = OFFSET * 2;  
        static const uint8_t MODE                  = OFFSET * 3;    

        static const uint8_t PIN                   = OFFSET * 4;    
        static const uint8_t RATE                  = OFFSET * 5; 
        static const uint8_t MINIMUM               = OFFSET * 6;
        static const uint8_t LIMIT                 = OFFSET * 7;

        static const uint8_t CLEAR                 = OFFSET * 8;
        static const uint8_t RESET                 = OFFSET * 9;
        static const uint8_t FORMAT                = OFFSET * 10;

        static const uint8_t CURRENT_TRANSA        = OFFSET * 11;
        static const uint8_t CURRENT_AMOUNT        = OFFSET * 12;
        static const uint8_t CURRENT_TRANSC        = OFFSET * 13;
        static const uint8_t CURRENT_CREDIT        = OFFSET * 14;

        static const uint8_t CURRENT_POWER         = OFFSET * 15;
        static const uint8_t CURRENT_SERVE         = OFFSET * 16;


        static const uint8_t LIFETIME_TRANSA       = OFFSET * 17;
        static const uint8_t LIFETIME_AMOUNT       = OFFSET * 18;
        static const uint8_t LIFETIME_TRANSC       = OFFSET * 19;
        static const uint8_t LIFETIME_CREDIT       = OFFSET * 20;

        static const uint8_t LIFETIME_POWER        = OFFSET * 21;
        static const uint8_t LIFETIME_SERVE        = OFFSET * 22;

        //first
        void setFirst(uint32_t first);
        uint32_t getFirst(void); 
        //firmware
        void setFirmware(uint32_t firmware);
        uint32_t getFirmware(void); 
        //mode
        void setMode(uint32_t mode);
        uint32_t getMode(void); 
        //clear
        void clear(uint32_t date);
        uint32_t getClearDate(void);
        //reset
        void reset(uint32_t date);
        uint32_t getResetDate(void);
        //format
        void format(uint32_t date);
        uint32_t getFormatDate(void);
        //pin
        void setPin(uint32_t pin);
        uint32_t getPin(void);
        //rate
        void setRate(uint32_t rate);
        uint32_t getRate(void);
        //minimum
        void setMinimum(uint32_t min);
        uint32_t getMinimum(void);
        //limit
        void setLimit(uint32_t lim);
        uint32_t getLimit(void);

        //transA
        void incrementTransA(uint16_t value);
        uint32_t getCurrentTransA(void);
        uint32_t getLifetimeTransA(void);
        //amount
        void incrementAmount(uint16_t value);
        uint32_t getCurrentAmount(void);
        uint32_t getLifetimeAmount(void);

        //transA
        void incrementTransC(uint16_t value);
        uint32_t getCurrentTransC(void);
        uint32_t getLifetimeTransC(void);
        
        //credit
        void incrementCredit(uint16_t value);
        uint32_t getCurrentCredit(void);
        uint32_t getLifetimeCredit(void);

        //serve
        void incrementServe(uint16_t value);
        uint32_t getCurrentServe(void);
        uint32_t getLifetimeServe(void);
      
        //power
        void incrementPower(uint16_t value);
        uint32_t getCurrentPower(void);
        uint32_t getLifetimePower(void);

    private:
        uint32_t _pin = 123456;    //Default pin is 123456 
        uint32_t _rate = 120;      //Default rate is (1peso = 2mins)
        uint32_t _limit = 10000;   //Default limit 10 thousand pesos
        uint32_t _zero = 0;        //Default is zero value

};
#endif // _STORAGE_H
