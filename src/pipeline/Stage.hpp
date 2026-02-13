#ifndef STAGE_H
#define STAGE_H

#include "DataPacket.hpp"

class Stage
{
    public:
        virtual DataPacket process(const DataPacket& input) = 0;
    };

#endif