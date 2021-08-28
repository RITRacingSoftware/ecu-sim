#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H

#define CAN_MESSAGE_LEN 8

namespace ecusim
{
    class CanMessage
    {
        public:
            int id;
            char data[CAN_MESSAGE_LEN];
            unsigned short int dlc;

            // friend bool operator < (const CanMessage& lhs, const CanMessage& rhs);
            // friend bool operator > (const CanMessage& lhs, const CanMessage& rhs);    
    };
}

#endif