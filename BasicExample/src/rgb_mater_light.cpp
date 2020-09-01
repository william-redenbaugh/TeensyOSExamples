#include "rgb_master_light.hpp"

/* 
*   @brief The rgb values that 
*/
static RgbColor rgb_val; 
static uint8_t brightness = 4; 

static inline void setup_pwm_pin(int pin); 
void setup_rgb_led_gpio(void); 
void set_main_rgb_value_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_main_rgb_value(uint8_t r, uint8_t g, uint8_t b); 
void set_brighness(uint8_t b);
RgbColor get_main_rgb_value(void);
HsvColor get_main_hsv_value(void); 
static inline uint8_t max_value(uint8_t a, uint8_t b, uint8_t c); 
void fade_main_hsv(HsvColor col, uint8_t increment_amount); 

/*!
*   @brief Tiny little helper function that makes code a little easier to understand.
*/  
static inline void setup_pwm_pin(int pin){
    pinMode(pin, OUTPUT); 
    analogWriteFrequency(pin, 36621.09); 
}

/*!
*   @brief Setting up the rgb led gpio
*/
void setup_rgb_led_gpio(void){
    // Setups our PWM Gpio

    analogWriteResolution(12);
    setup_pwm_pin(RED_LED_GPIO); 
    setup_pwm_pin(GREEN_LED_GPIO); 
    setup_pwm_pin(BLUE_LED_GPIO); 
}

/*!
*   @brief Allows us to set the Master LED to a specifc hsv value 
*   @param uint8_t hue value 
*   @param uint8_t saturation value
*   @param uint8_t value(brightness)
*/
void set_main_rgb_value_hsv(uint8_t h, uint8_t s, uint8_t v){
    // Convert to HSV color space. 
    HsvColor hsv = {h, s, v}; 
    RgbColor rgb = HsvToRgb(hsv); 

    // Update the LED
    set_main_rgb_value(rgb.r, rgb.g, rgb.b); 
}

/*!
*   @brief Allows us to set the Master LED to a specifc hsv value 
*   @param HsvColor hsv color
*/
void set_main_rgb_value_hsv(HsvColor hsv){
    RgbColor rgb = HsvToRgb(hsv); 

    // Update the LED
    set_main_rgb_value(rgb.r, rgb.g, rgb.b); 
}

/*!
*   @brief Sets the main rgb value. 
*   @param uint8_t red
*   @param uint8_t green
*   @param uint8_t blue
*/
void set_main_rgb_value(uint8_t r, uint8_t g, uint8_t b){
    // Save our RGB values. 
    rgb_val.r = r * brightness; 
    rgb_val.g = g * brightness; 
    rgb_val.b = b * brightness;

    // Drive the proper RGB LED values 
    analogWrite(RED_LED_GPIO, r); 
    analogWrite(GREEN_LED_GPIO, g); 
    analogWrite(BLUE_LED_GPIO, b); 
}

/*!
*   @brief Sets the brightness of the LED
*   @param uint8_t b
*   @note This only takes brightness values from 0 to 32. 
*/
void set_brighness(uint8_t b){
    if (b >= 32)
        b = 32; 
    brightness = b;    
}

/*!
*   @brief So we can get the main RGB value 
*   @returns RgbColor rgb value
*/
RgbColor get_main_rgb_value(void){
    return rgb_val; 
}

/*!
*   @brief So we can get the main HSV value 
*   @returns HsvColor rgb value
*/
HsvColor get_main_hsv_value(void){
    return RgbToHsv(rgb_val); 
}

/*!
*   @brief Finding the largest possible value 
*   @note Just a helper function that helps us deal with coloring stuff
*   @return uint8_t maximum value 
*   @param uint8_t a
*   @param uint8_t b
*   @param uint8_t b
*/
static inline uint8_t max_value(uint8_t a, uint8_t b, uint8_t c){
    if(a >= b)
        // A is greater or equal value to b or c
        if(a >= c)
            return a; 
    else
        // B is greate or equal value to a or c
        if(b >= c)
            return b;

    // Since a and b were not as large as b, we return c
    return c; 
}

/*!
*   @brief Allows us to fade the hsv color by a certain amount
*   @param HsvColor col(color we want to fade to )
*   @param uint8_t increment amount(how fast we want to fade based of 100fps animation)
*/
void fade_main_hsv(HsvColor col, uint8_t increment_amount){
    HsvColor prev_col = RgbToHsv(rgb_val); 
    while(1){
        int x = 0; 

        if(abs(prev_col.h - col.h) > increment_amount){
            prev_col.h = prev_col.h + increment_amount; 
        }
        else{
            prev_col.h = col.h;
            x++; 
        }

        if(abs(prev_col.s - col.s) > increment_amount){
            prev_col.s = prev_col.s + increment_amount; 
        }
        else{
            prev_col.s = col.s;
            x++; 
        }

        if(abs(prev_col.v - col.v) > increment_amount){
            prev_col.v = prev_col.v + increment_amount; 
        }
        else{
            prev_col.v = col.v; 
            x++;     
        }
        
        if(x == 3)
            break; 

        // Set the color value 
        set_main_rgb_value_hsv(prev_col);
        os_thread_delay_ms(RGB_LED_FRAME_TIME); 
    }
}