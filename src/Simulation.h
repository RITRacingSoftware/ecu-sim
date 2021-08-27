#ifndef SIMULATION_CLASS_H
#define SIMULATION_CLASS_H

#include<vector>

#include "Ecu.h"

namespace ecusim
{
    class Simulation
    {
        public: 
            void add_ecu(Ecu* ecu);
            void run_ms(int);
            ~Simulation();
            
        private:
            void tick();
            std::vector<Ecu*> ecu_list;
            std::vector<std::vector<CanMessage_s>*> message_matrix;
    };
}

#endif