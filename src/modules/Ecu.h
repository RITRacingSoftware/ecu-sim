#ifndef ECU_H
#define ECU_H

#include <string>
#include <vector>

#include "CanMsg.h"

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
            virtual void injectCan(CanMsg) = 0;
            virtual void set(std::string, float) = 0;
            virtual float get(std::string) = 0;
            std::vector<CanMsg>* emptyCan(void);

        protected:
            std::vector<CanMsg> can_outbox;
    };
}

#endif