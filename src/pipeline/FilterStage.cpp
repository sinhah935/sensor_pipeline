#include "FilterStage.hpp"

FilterStage::FilterStage()
{
    index = 0;
    int i;
    
    //length of history buffer is 5
    for(i = 0; i < 5; i++)
    {
        history[i] = 0.0f;
    }
}

DataPacket FilterStage::process(const DataPacket& input)
{
    history[index] = input.getDistance();
    index = (index + 1) % 5; //circular buffer logic

    return input;

};