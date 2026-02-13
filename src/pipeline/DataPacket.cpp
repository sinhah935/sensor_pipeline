#include "DataPacket.hpp"

//constructor
DataPacket::DataPacket(const sensor_data& data)
{
    distance = data.distance;
    time_stamp = data.time_stamp;
    valid = data.valid;
}

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

void DataPacket::setDistance(float distance) 
{
    DataPacket::distance = distance;
    
};

