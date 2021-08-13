#ifndef ECU_H
#define ECU_H

#include <string>
#include <vector>

#include "CanMessage.h"

namespace ecusim
{
    typedef struct
    {
        void (*fun_ptr)(void);
        unsigned int period_ms;
    } TimedFunction_s;

    class Ecu
    {
        public:
            virtual void tick(void) = 0;
            virtual void injectCan(CanMessage_s) = 0;
            virtual void set(std::string) = 0;
            std::vector<CanMessage_s>* emptyCan(void);
        
        private:
            std::vector<CanMessage_s> can_outbox;
    };
}

#endif