#include "CanMessage.h"
#include "Simulation.h"

using namespace ecusim;

void Simulation::add_ecu(Ecu* ecu)
{
    this->ecu_list.push_back(ecu);
}

void Simulation::tick()
{
    this->message_matrix.clear();

    std::vector<Ecu*>::iterator ecu_iter;
    for (ecu_iter = this->ecu_list.begin(); ecu_iter < this->ecu_list.end(); ecu_iter++)
    {
        Ecu* ecu = *ecu_iter;
        ecu->tick();
        this->message_matrix.push_back(ecu->empyCan());
    }

    std::vector<std::vector<CanMessage>>::iterator matrix_iter;
    for (matrix_iter = this->message_matrix.begin(); matrix_iter < this->message_matrix.end(); message_matrix++)
    {
        // time for priority queue
    }


}

void Simulation::run_ms(int num_ticks)
{
    for (int i = 0; i < num_ticks; i++) this->tick();
}

Simulation::~Simulation()
{
    std::vector<Ecu*>::iterator ecu;
    for (ecu = this->ecu_list.begin(); ecu < this->ecu_list.end(); ecu++)
    {
        delete *ecu;
    }
}

