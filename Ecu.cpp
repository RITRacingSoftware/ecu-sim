#include "Ecu.h"

using namespace ecusim;

std::vector<CanMessage_s>* Ecu::emptyCan(void)
{
    std::vector<CanMessage_s>* ret = new std::vector<CanMessage_s>;
    ret->swap(this->can_outbox);
    return ret;
}