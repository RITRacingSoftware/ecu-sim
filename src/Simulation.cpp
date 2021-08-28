#include <algorithm>
#include <queue>
#include <iostream>

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
    std::vector<std::vector<CanMessage>*>::iterator matrix_iter;
    for (matrix_iter = this->message_matrix.begin(); matrix_iter < this->message_matrix.end(); ++matrix_iter)
    {
        if ((*matrix_iter)->size() > longest_matrix_len) longest_matrix_len = (*matrix_iter)->size();
    }

    // "Send" each CAN message to each ECU
    // This iterates through the matrices breadth-first.
    for (int i = 0; i < longest_matrix_len; i++)
    {
        // Each of these messages was sent at the same time. Need to prioritize by CAN ID just like CAN hardware does
        auto compare = [](CanMessage lhs, CanMessage rhs)
        {
            return lhs.id > rhs.id;
        };

        // "same time" means same index in respective ecu list here
        std::priority_queue<CanMessage, std::vector<CanMessage>, decltype(compare)> ordered_msgs(compare);
        for (matrix_iter = this->message_matrix.begin(); matrix_iter < this->message_matrix.end(); ++matrix_iter) 
        {
            if ((*matrix_iter)->size() > i)
            {
                ordered_msgs.push((*matrix_iter)->at(i));
            }
        }

        // Deliver CAN messages to ECUs in order
        CanMessage next_msg;
        while(ordered_msgs.size() > 0)
        {
            // get the next msg
            next_msg = ordered_msgs.top();
            int ecunum = 0;
            for (ecu_iter = this->ecu_list.begin(); ecu_iter < this->ecu_list.end(); ecu_iter++)
            {
                struct compare
                {
                    CanMessage key;
                    compare(CanMessage const &i): key(i) {}
                
                    bool operator()(CanMessage const &i) {
                        return (i.id == key.id);
                    }
                };
                auto ecu_messages = this->message_matrix.at(ecunum);
                // don't return CAN messages to sender.
                if (!std::any_of(ecu_messages->begin(), ecu_messages->end(), compare(next_msg)))
                {
                    Ecu* ecu = *ecu_iter;
                    ecu->injectCan(next_msg);
                }

                ecunum++;
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
    // std::vector<Ecu*>::iterator ecu;
    // for (ecu = this->ecu_list.begin(); ecu < this->ecu_list.end(); ++ecu)
    // {
    //     delete *ecu;
    // }
}

