#ifndef SENSOR_H
#define SENSOR_H

#include "esp_err.h"

//should be 12 bytes of memory
typedef struct {
    float distance;
    float time_stamp;
    int valid;
    
} sensor_data;

void init_sensor();
esp_err_t read_sensor_data(sensor_data* data);

#endif