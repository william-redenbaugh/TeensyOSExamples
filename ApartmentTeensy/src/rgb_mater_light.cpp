#include "rgb_master_light.hpp"

/* 
*   @brief The rgb values that 
*/
static RgbColor rgb_val; 
static uint8_t brightness = 3; 

static inline void setup_pwm_pin(int pin); 
void setup_rgb_led_gpio(void); 
void set_main_rgb_value_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_main_rgb_value(uint8_t r, uint8_t g, uint8_t b); 
void set_brighness(uint8_t b);
RgbColor get_main_rgb_value(void);
HsvColor get_main_hsv_value(void); 
void set_main_rgb_kelvin(uint32_t kelvin); 

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
    rgb_val.r = r; 
    rgb_val.g = g; 
    rgb_val.b = b;

    // Drive the proper RGB LED values 
    analogWrite(RED_LED_GPIO, r * brightness); 
    analogWrite(GREEN_LED_GPIO, g * brightness); 
    analogWrite(BLUE_LED_GPIO, b * brightness); 
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
*   @brief Sets the big RGB LED to a particular Kelvin value. 
*   @param uint32_t kelvin in degrees. 
*/
void set_main_rgb_kelvin(uint32_t kelvin){
    double adj_temp = kelvin/100;
    uint8_t red; 
    uint8_t blue; 
    uint8_t green; 

    // first we need to deal with the Red calculation!
    // red_cutoff!
    if(adj_temp <= 66){
    red = 255;     
    }
    // some mathematical calculations!
    else{
        double adj_red = (adj_temp  - 60); 
        adj_red = 329.698727446 * (pow(adj_red, -0.1332047592));

        if(adj_red > 255)
            adj_red = 255;   
        if(adj_red < 0)
            adj_red = 0; 
            
        red = uint8_t(adj_red);
    }

    // calulcate green
    double adj_green; 

    if(adj_temp <= 66){
        adj_green = adj_temp;
        adj_green = ((log(adj_green)) * 99.4708025861) - 161.1195681661;
    }
    else{
        adj_green = adj_temp - 60;
        adj_green = 288.1221695283 * (pow(adj_green, -0.0755148492));
    }
    // more math and simple logic here!
    if(adj_green > 255)
        adj_green = 255;   
    
    if(adj_green < 0)
        adj_green = 0;   
    
    green = uint8_t(adj_green);

    if(adj_temp >= 66)
        blue = 255; 
    else{
        // finishing math and computer logic here...
        if(adj_temp <= 19){
            blue = 0;   
        }  
        else{
            double adj_blue = adj_temp - 10; 
            adj_blue = ((log(adj_blue))  * 138.5177312231) - 305.0447927307;
            if(adj_blue > 255){
                adj_blue = 255;   
            }
            if(adj_blue < 0){
                adj_blue = 0;   
            }
            blue = uint8_t(adj_blue);
        }
    }
    set_main_rgb_value(red, green, blue); 
}