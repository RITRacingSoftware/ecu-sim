#include "Ecu.h"

using namespace ecusim;

std::vector<CanMsg>* Ecu::emptyCan(void)
{
    std::vector<CanMsg>* ret = new std::vector<CanMsg>;
    ret->swap(this->can_outbox);
    return ret;
}