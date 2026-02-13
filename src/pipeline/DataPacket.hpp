#ifndef DATA_PACKET_H
#define DATA_PACKET_H

extern "C" {
    #include "drivers/sensor.h"
}

class DataPacket {
    private:
        float distance;
        float time_stamp;
        bool valid;

    public:
        DataPacket(const sensor_data& data);

        float getDistance() const;
        float getTimeStamp() const;
        bool isValid() const;
        void setDistance(float distance);

};

#endif