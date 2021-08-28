#include "Ecu.h"

using namespace ecusim;

std::vector<CanMessage>* Ecu::emptyCan(void)
{
    std::vector<CanMessage>* ret = new std::vector<CanMessage>;
    ret->swap(this->can_outbox);
    return ret;
}