#include "sensor.h"

static float distance = 0.0;
static uint32_t ticks = 0; // number of ticks since the sensor was last read

void init_sensor() {
    //just for simulation, will configure sensor when ready
    distance = 51.0;
    ticks = 0;
}

//returns esp_err_t enum value determining if the read was successful or not
esp_err_t read_sensor_data(sensor_data* data)
{
    distance += 0.3;
    ticks += 1;

    data->distance = distance;
    data->time_stamp = ticks * 0.01;
    data->valid = 1;

    return ESP_OK;
}
