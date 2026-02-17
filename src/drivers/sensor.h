#ifndef SENSOR_H
#define SENSOR_H

#include "esp_err.h"

//This ifdef allows for C++, the linker will look for C functions
#ifdef __cplusplus
extern "C" {
#endif

//should be 12 bytes of memory
typedef struct {
    float distance; // in meters
    float time_stamp; // time since boot in seconds
    int valid;
    
} sensor_data;

void init_sensor();
esp_err_t read_sensor_data(sensor_data* data);

#ifdef __cplusplus
}
#endif
#endif