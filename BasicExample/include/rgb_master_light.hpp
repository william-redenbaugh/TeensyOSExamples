#ifndef _RGB_MASTER_LIGHT_HPP
#define _RGB_MASTER_LIGHT_HPP

#include <Arduino.h>

// RTOS stuff
#include "OS/OSThreadKernel.h"
#include "OS/OSMutexKernel.h"

// RTOS based Device managers 
#include "HAL/OSSerial.h"

// Low priority work thread stuff
#include "MODULES/LPWORK/lp_work_thread.h"

// Message management stuff
#include "MODULES/PROTOCALLBACKS/teensy_coms.h"

// Color Conversion and rgb led structs. 
#include "hsv_rgb_conv.hpp"

#define RED_LED_GPIO   2
#define GREEN_LED_GPIO 3
#define BLUE_LED_GPIO  4

/*!
*   @brief The speed that we want RGB animations to go at
*/
#define RGB_LED_FRAMERATE 100

/*!
*   @brief The amount of time in MS that each RGB LED frame takes 
*/
#define RGB_LED_FRAME_TIME 1000 / RGB_LED_FRAMERATE

void setup_rgb_led_gpio(void); 
void set_main_rgb_value_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_main_rgb_value_hsv(HsvColor hsv);
void set_main_rgb_value(uint8_t r, uint8_t g, uint8_t b); 
void set_brighness(uint8_t b);
RgbColor get_main_rgb_value(void);
HsvColor get_main_hsv_value(void);
void fade_main_hsv(HsvColor col, uint8_t increment_amount);  

#endif 