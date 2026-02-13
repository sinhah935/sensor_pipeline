#include "LoggerStage.hpp"

DataPacket LoggerStage::process(const DataPacket& input)
{
    if(input.isValid())
    {
        printf("Average Distance: %f Timestamp: %f\n",
            input.getDistance(), input.getTimeStamp());
    }
    else
    {
        printf("Invalid data...\n");
    }

    return input;
};