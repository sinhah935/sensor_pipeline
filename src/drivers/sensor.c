#include "sensor.h"
#include <driver/gpio.h>
#include "esp_timer.h"
#include "esp_rom_sys.h"

#define GPIO_TRIG 25
#define GPIO_ECHO 26

#define TIMEOUT 30000 //30 ms
#define SOUND_SPEED 343 // meters/s

/*
        REAL SENSOR VERSION BEGIN
*/

/*
    This function should:
        - Initialize the GPIO pins
        - TRIG pin should be set to output
        - ECHO pin should set to input(taking in the data)
*/
void init_sensor()
{
    //Must set Trig to output
    //.pull_up_en = enable/disable pull up resistance
    //.pull_down_en = enable/disable pull down resistance
    gpio_config_t io_conf_trig = 
    {
        .pin_bit_mask = (1ULL << GPIO_TRIG), //Select GPIO 25(for TRIG)
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };

    gpio_config_t io_conf_echo =
    {
        .pin_bit_mask = (1ULL << GPIO_ECHO),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };

    //might have to create fault checks for these, esp_err_t gpio_config
    gpio_config(&io_conf_trig);
    gpio_config(&io_conf_echo);

    gpio_set_level(GPIO_TRIG, 0); //for initialization, set TRIG to low pulse
};


/*
    To take the distance:
        - set the TRIG pin to HIGH for 10 microseconds(us) via esp_rom_delay_us
        - ECHO will go to HIGH auto, get initial timestamo when this happens(esp_timer_get_time)
        - When ECHO hits low, record end timestamp
        - Use d = v * t, where v is the speed of sound. d may need to be divided by 2 to account for the ultrasound coming back
*/
esp_err_t read_sensor_data(sensor_data* data)
{
    int64_t start, finish, wait_start, wait_end, pulse_width_us;
    float distance_m; //in meters

    gpio_set_level(GPIO_TRIG,0);
    esp_rom_delay_us(2);//start off low for 2 microseconds
    gpio_set_level(GPIO_TRIG, 1); //set to 1 
    esp_rom_delay_us(10); //busy-wait for 10 seconds, This will hopefully change to be asyncronous
    gpio_set_level(GPIO_TRIG,0);

    //The time of when ECHO gets high back to low will first be done via polling
    //Interrupt driven will be done after

    //POLLING IMPLEMENTATION
    wait_start = esp_timer_get_time(); //in us
    while(gpio_get_level(GPIO_ECHO) == 0)
    {
        //if it takes longer than 30ms, throw an error
        if(esp_timer_get_time() - wait_start > TIMEOUT)
        {
            data->valid = 0;
            return ESP_FAIL;
        }
    }
    start = esp_timer_get_time(); //Once the level is set to 1(high), start the timer

    wait_end = esp_timer_get_time(); //in us
    while(gpio_get_level(GPIO_ECHO) == 1)
    {
        //if it takes longer than 30ms, throw an error
        if(esp_timer_get_time() - wait_end > TIMEOUT)
        {
            data->valid = 0;
            return ESP_FAIL;
        }
    }
    finish = esp_timer_get_time();
    pulse_width_us = finish - start; //total time of the ultrasound, make sure pulse_width_us is positive

    //Convert time from microseconds to seconds, then multiply the time by velocity of sound and divide by 2
    //0.0001715 = 343 / 2 / 1e6
    distance_m = pulse_width_us * 0.0001715f; //get distance in meters

    //DEBUGGING PURPOSES
    printf("Distance: %.3f m\n", distance_m);


    data->distance = distance_m;
    data->time_stamp = (float)finish; //seconds
    data->valid = 1;

    return ESP_OK;
}

/*
        REAL SENSOR VERSION END
*/





/*
        SIMULATION VERSION BEGIN: WILL OPTIMIZE FOR EASY SWITCHING LATER
*/

// static float distance = 0.0;
// static uint32_t ticks = 0; // number of ticks since the sensor was last read

// void init_sensor() {
//     //just for simulation, will configure sensor when ready
//     distance = 51.0;
//     ticks = 0;
// }

// //returns esp_err_t enum value determining if the read was successful or not
// esp_err_t read_sensor_data(sensor_data* data)
// {
//     distance += 0.3;
//     ticks += 1;

//     data->distance = distance;
//     data->time_stamp = ticks * 0.01;
//     data->valid = 1;

//     return ESP_OK;
// }

/*
        SIMULATION VERSION END
*/


