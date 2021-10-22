#ifndef CAN_LOGGER_H
#define CAN_LOGGER_H
#include "Ecu.h"

using namespace ecusim;

/**
 * Used to log CAN messages in BLF format.
 * As long as this ECU is part of the sim, 
 * it adds each message transmitted on the bus to a BLF log file.
 */
class CanLogger: public Ecu {
    public:
        CanLogger(char* fileName);
        ~CanLogger(void);
        void tick(void);
        void injectCan(ecusim::CanMsg);
        void set(std::string, float);
        float get(std::string);
    
    private:
        uint64_t currentTimeMs;
};

#endif // CAN_LOGGER_H