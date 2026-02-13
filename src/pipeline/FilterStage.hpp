#ifndef FILTER_H
#define FILTER_H

#include "Stage.hpp"

static constexpr int HISTORY_SIZE = 5; //C++ way for defines
//#define HISTORY_SIZE 5


class FilterStage: public Stage
{
    private:
        float history[HISTORY_SIZE];
        int index;

    public:
        FilterStage();
        DataPacket process(const DataPacket& input) override;
};

#endif