#include "FilterStage.hpp"

FilterStage::FilterStage()
{
    index = 0;
    int i;
    
    //length of history buffer is 5
    for(i = 0; i < HISTORY_SIZE; i++)
    {
        history[i] = 0.0f;
    }
}

DataPacket FilterStage::process(const DataPacket& input)
{
    float sum = 0.0f;
    float avg = 0.0f;

    history[index] = input.getDistance();
    index = (index + 1) % HISTORY_SIZE; //circular buffer logic

    int i;
    for(i = 0; i < HISTORY_SIZE; i++)
    {
        sum += history[i];
    }

    avg = sum / HISTORY_SIZE;

    //create a copy to output a modded version of the original
    DataPacket output = input;
    output.setDistance(avg);

    return output;

};