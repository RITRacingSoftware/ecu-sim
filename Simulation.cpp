#include <queue>

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

    // tick all the ecus and get all the can messages sent
    std::vector<Ecu*>::iterator ecu_iter;
    for (ecu_iter = this->ecu_list.begin(); ecu_iter < this->ecu_list.end(); ++ecu_iter)
    {
        Ecu* ecu = *ecu_iter;
        ecu->tick();
        this->message_matrix.push_back(ecu->emptyCan());
    }

    // Figure out the most CAN messages any ECU sent
    int i = 0;
    int longest_matrix_len = 0;

    std::vector<std::vector<CanMessage_s>*>::iterator matrix_iter;
    for (matrix_iter = this->message_matrix.begin(); matrix_iter < this->message_matrix.end(); ++matrix_iter)
    {
        if ((*matrix_iter)->size() > longest_matrix_len) longest_matrix_len = (*matrix_iter)->size();
    }

    // "Send" each CAN message to each ECU
    for (int i = 0; i < longest_matrix_len; i++)
    {
        // sort by id
        auto compare = [](CanMessage_s lhs, CanMessage_s rhs)
        {
            return lhs.id - rhs.id;
        };

        std::priority_queue<CanMessage_s, std::vector<CanMessage_s>, decltype(compare)> ordered_msgs(compare);
        for (matrix_iter = this->message_matrix.begin(); matrix_iter < this->message_matrix.end(); ++matrix_iter) 
        {
            if ((*matrix_iter)->size() > i)
            {
                ordered_msgs.push((*matrix_iter)->at(i));
            }
        }

        // Deliver CAN messages to ECUs in order
        CanMessage_s next_msg;
        while(ordered_msgs.size() > 0)
        {
            next_msg = ordered_msgs.top();
            for (ecu_iter = this->ecu_list.begin(); ecu_iter < this->ecu_list.end(); ecu_iter++)
            {
                Ecu* ecu = *ecu_iter;
                ecu->injectCan(next_msg);
            }

            ordered_msgs.pop();
        }
    }


}

void Simulation::run_ms(int num_ticks)
{
    for (int i = 0; i < num_ticks; i++) this->tick();
}

Simulation::~Simulation()
{
    std::vector<Ecu*>::iterator ecu;
    for (ecu = this->ecu_list.begin(); ecu < this->ecu_list.end(); ++ecu)
    {
        delete *ecu;
    }
}

