#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "drivers/sensor.h"
#include "pipeline/FilterStage.hpp"
#include "pipeline/LoggerStage.hpp"

extern "C" int app_main() 
{
    init_sensor(); //initalize the sensor

    //init the stage objects
    FilterStage filter;
    LoggerStage logger;

    //for now keep as for loop, change to while(1) or freeRTOS later
    while(1)
    {
        sensor_data raw_data; //pointer to raw_data
        read_sensor_data(&raw_data); //takes in sensor data

        //create the wrapper for the data struct sensor_data
        DataPacket packet(raw_data);

        packet = filter.process(packet);
        packet = logger.process(packet);

        //Add a 60 ms delay
        vTaskDelay(pdMS_TO_TICKS(60));
    }
    
    return 0;
}