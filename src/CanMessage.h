#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H

#define CAN_MESSAGE_LEN 8

namespace ecusim
{
    typedef struct 
    {
        int id;
        char* data[CAN_MESSAGE_LEN];
        unsigned short int dlc;    
    } CanMessage_s;
}

#endif