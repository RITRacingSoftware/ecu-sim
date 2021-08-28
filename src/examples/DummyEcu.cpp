#include <iostream>

#include "DummyEcu.h"

using namespace ecusim;

DummyEcu::DummyEcu(std::string name)
{
    this->name = name;
}

void DummyEcu::tick(void)
{
    std::cout << this->name << ": ticking!" << std::endl;
}

void DummyEcu::injectCan(CanMessage msg)
{
    std::cout << this->name << ": received CAN message with ID: " << msg.id << std::endl;
}

void DummyEcu::set(std::string key, float value)
{
    if (key == "CAN")
    {
        CanMessage msg;
        msg.id = value;
        msg.data[0] = 'a';
        msg.dlc = 8;
        this->can_outbox.push_back(msg);
    }
    else 
    {
        std::cout << this->name << ": set value '" << key << "' to " << value << std::endl;
    }
}