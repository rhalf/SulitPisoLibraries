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
        static const uint8_t PKWH                  = OFFSET * 8;

        static const uint8_t CLEAR                 = OFFSET * 9;
        static const uint8_t RESET                 = OFFSET * 10;
        static const uint8_t FORMAT                = OFFSET * 11;

        static const uint8_t CURRENT_TRANSA        = OFFSET * 12;
        static const uint8_t CURRENT_AMOUNT        = OFFSET * 13;
        static const uint8_t CURRENT_TRANSC        = OFFSET * 14;
        static const uint8_t CURRENT_CREDIT        = OFFSET * 15;
        static const uint8_t CURRENT_TRANSF        = OFFSET * 16;
        static const uint8_t CURRENT_FREE          = OFFSET * 17;

        static const uint8_t CURRENT_POWER         = OFFSET * 18;
        static const uint8_t CURRENT_SERVE         = OFFSET * 19;
        static const uint8_t CURRENT_TIME          = OFFSET * 20;


        static const uint8_t LIFETIME_TRANSA       = OFFSET * 21;
        static const uint8_t LIFETIME_AMOUNT       = OFFSET * 22;
        static const uint8_t LIFETIME_TRANSC       = OFFSET * 23;
        static const uint8_t LIFETIME_CREDIT       = OFFSET * 24;
        static const uint8_t LIFETIME_TRANSF       = OFFSET * 25;
        static const uint8_t LIFETIME_FREE         = OFFSET * 26;

        static const uint8_t LIFETIME_POWER        = OFFSET * 27;
        static const uint8_t LIFETIME_SERVE        = OFFSET * 28;
        static const uint8_t LIFETIME_TIME         = OFFSET * 29;

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
        //pkwh
        void setPkwh(uint32_t pkwh);
        uint32_t getPkwh(void);

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

        //transF
        void incrementTransF(uint16_t value);
        uint32_t getCurrentTransF(void);
        uint32_t getLifetimeTransF(void);

        //free
        void incrementFree(uint16_t value);
        uint32_t getCurrentFree(void);
        uint32_t getLifetimeFree(void);
        
        //serve
        void incrementServe(uint16_t value);
        uint32_t getCurrentServe(void);
        uint32_t getLifetimeServe(void);
      
        //power
        void incrementPower(uint16_t value);
        uint32_t getCurrentPower(void);
        uint32_t getLifetimePower(void);

        //time
        void incrementTime(uint16_t value);
        uint32_t getCurrentTime(void);
        uint32_t getLifetimeTime(void);

    private:
        uint32_t _pin = 123456;     //Default pin is 123456 
        //spc rate
        //uint32_t _rate = 180;       //Default rate is (1peso = 3m)
        //spm rate
        uint32_t _rate = 30;      //Default rate is (1peso = 30s)
        uint32_t _limit = 5000;     //Default limit 10 thousand pesos
        uint32_t _zero = 0;         //Default is zero value
        uint32_t _pkwh = 1500;      //Default is 15.00 pesos per kwh

};
#endif // _STORAGE_H
