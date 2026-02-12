#ifndef FILTER_H
#define FILTER_H

#include "Stage.hpp"


class FilterStage: public Stage
{
    private:
        float history[5];
        int index;

    public:
        FilterStage();
        DataPacket process(const DataPacket& input) override;
};

#endif