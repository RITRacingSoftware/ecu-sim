#ifndef DUMMY_ECU_H
#define DUMMY_ECU_H

#include "Ecu.h"

namespace ecusim 
{
    class DummyEcu: public Ecu 
    {
        public:
            DummyEcu(std::string);
            void tick(void);
            void injectCan(CanMsg);
            void set(std::string, float);
        
        private:
            std::string name;
    };
}


#endif // DUMMY_ECU_H