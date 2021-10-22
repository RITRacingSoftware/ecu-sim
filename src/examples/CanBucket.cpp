#include "CanBucket.h"
#include "BlfWriter.h"

void CanBucket::tick(void)
{
    // no processing required
}

void CanBucket::injectCan(ecusim::CanMsg msg)
{
    // log it!
    this->bucket.push_back(msg);
}
        
void CanBucket::set(std::string, float)
{
    // no set options
}

float CanBucket::get(std::string)
{
    // nothing to get
    return 0.0;
}

std::vector<CanMsg>* CanBucket::drain(void)
{
    std::vector<CanMsg>* ret = new std::vector<CanMsg>;
    ret->swap(this->bucket);
    return ret;
}
