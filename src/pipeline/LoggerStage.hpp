#ifndef LOGGER_H
#define LOGGER_H

#include "Stage.hpp"

class LoggerStage: public Stage
{
    public:
        DataPacket process(const DataPacket& input) override;

};

#endif