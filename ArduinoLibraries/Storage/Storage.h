#ifndef _STORAGE_H
#define _STORAGE_H

#include "Arduino.h"
#include "EEPROM.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>


class Storage {
    public:

        static const uint8_t OFFSET                = sizeof(uint32_t) + 0;
        
        static const uint8_t MODE                  = OFFSET * 0x00;    

        static const uint8_t PIN                   = OFFSET * 0x01;    
        static const uint8_t RATE                  = OFFSET * 0x02; 
        static const uint8_t MINIMUM               = OFFSET * 0x03; 

        static const uint8_t CURRENT_TRANSACT      = OFFSET * 0x10;
        static const uint8_t CURRENT_GROSS         = OFFSET * 0x11;
        static const uint8_t CURRENT_SERVE         = OFFSET * 0x12;
        static const uint8_t CURRENT_CREDIT        = OFFSET * 0x13;
        static const uint8_t CURRENT_POWER         = OFFSET * 0x14;

        static const uint8_t LIFETIME_TRANSACT     = OFFSET * 0x20;
        static const uint8_t LIFETIME_GROSS        = OFFSET * 0x21;
        static const uint8_t LIFETIME_SERVE        = OFFSET * 0x22;
        static const uint8_t LIFETIME_CREDIT       = OFFSET * 0x23;
        static const uint8_t LIFETIME_POWER        = OFFSET * 0x24;

        static const uint8_t CLEAR                 = OFFSET * 0x30;
        static const uint8_t RESET                 = OFFSET * 0x31;
        static const uint8_t FORMAT                = OFFSET * 0x32;
        

        Storage(void);
        void destroy(void);
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
        //transaction
        void incrementTransaction(uint8_t value);
        uint32_t getCurrentTransaction(void);
        uint32_t getLifetimeTransaction(void);
        //gross
        void incrementGross(uint8_t value);
        uint32_t getCurrentGross(void);
        uint32_t getLifetimeGross(void);
        //serve
        void incrementServe(uint8_t value);
        uint32_t getCurrentServe(void);
        uint32_t getLifetimeServe(void);
        //credit
        void incrementCredit(uint8_t value);
        uint32_t getCurrentCredit(void);
        uint32_t getLifetimeCredit(void);
        
        //power
        void incrementPower(uint8_t value);
        uint32_t getCurrentPower(void);
        uint32_t getLifetimePower(void);

    private:
        uint32_t _pin = 123456;    //Default pin is 123456 
        uint32_t _rate = 60;       //Default rate is coin1 : 60s (1peso = 1min)
        uint32_t _zero = 0;        //Default is zero value


};
#endif // _STORAGE_H
