#ifndef CAN_BUCKET_H
#define CAN_BUCKET_H
#include "Ecu.h"

using namespace ecusim;

/**
 * Collects CAN messages for future use.
 * Each CAN message received is stored in order.
 * Example: VcHandle uses this to store CAN messages during a sim run 
 * and uses them to apply changes to the CAN signal database.
 */
class CanBucket: public Ecu {
    public:
        void tick(void);
        void injectCan(ecusim::CanMsg);
        void set(std::string, float);
        float get(std::string);
        std::vector<CanMsg>* drain(void);
    
    private:
        std::vector<CanMsg> bucket;
};

#endif // CAN_BUCKET_H