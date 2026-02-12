#include "DataPacket.hpp"

class Stage 
{
    public:
        virtual DataPacket process(const DataPacket& input) = 0;
};