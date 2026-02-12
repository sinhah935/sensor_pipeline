#include "DataPacket.hpp"

float DataPacket::getDistance() const 
{
    return DataPacket::distance;
};

float DataPacket::getTimeStamp() const
{
    return DataPacket::time_stamp;
};

bool DataPacket::isValid() const
{
    return DataPacket::valid;
};

