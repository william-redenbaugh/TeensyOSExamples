#include "rgb_runtime_thread.hpp"

/*!
*   @brief The stack and defined stack size of our RGB runtime thread 
*/
#define LED_MATRIX_RUNTIME_STACK_SIZE 256
static uint32_t rgb_runtime_stack[LED_MATRIX_RUNTIME_STACK_SIZE];
#undef LED_MATRIX_RUNTIME_STACK_SIZE

void rgb_message_callback(MessageReq *msg); 
void start_rgb_runtime_thread(void); 
static void rgb_runtime_thread(void *parameters); 
static inline void rgb_loop(void); 

/*!
*   @brief The data that will hold our next LED data animation
*/
static LEDData next_led_data; 

/*!
*   @brief The signal that tells the program that another LED message has arrived.
*/
static OSSignal LEDMessageSignal;

/*!
*   @brief Message callback service routine that helps us get and unpack led message data. 
*   @note It works via "last man in", so whatever was the last data to be sent it will get executed.  
*/
void rgb_message_callback(MessageReq *msg){
    next_led_data = unpack_led_data(msg->data_ptr, msg->data_len);     
    LEDMessageSignal.signal(THREAD_SIGNAL_0); 
}

/*!
*   @brief The startup code for setting up the rgb runtime environment
*/
void start_rgb_runtime_thread(void){
    add_message_callback(MessageData_MessageType_LED_STRIP_DATA, &rgb_message_callback); 
    os_add_thread(&rgb_runtime_thread, NULL, sizeof(rgb_runtime_stack), rgb_runtime_stack);  
}

/*!
*   @brief The runtime thread itself for the rgb runtime environment
*/
static void rgb_runtime_thread(void *parameters){
    setup_rgb_led_gpio();  
    set_main_rgb_kelvin(4000);
    
    for(;;)
        rgb_loop(); 
}

/*!
*   @brief Loop program for rgb runtime(inline because I just want to keep indentation down)
*/
static inline void rgb_loop(void){
    LEDMessageSignal.wait_notimeout(THREAD_SIGNAL_0); 

    // Whatever type of message we get, we handle properly. 
    switch(next_led_data.message_type){
        // If we get kelvin data then we update to that data. 
        case(LEDData_MessageType_KELVIN_DATA):
        set_main_rgb_kelvin(next_led_data.kelvin_red_hue); 
        break; 

        // If we get RGB data, we update to that data. 
        case(LEDData_MessageType_RGB_DATA): 
        set_main_rgb_value(next_led_data.kelvin_red_hue, next_led_data.green_saturation, next_led_data.blue_value); 
        break; 

        // If we get HSV data we update the led to that data
        case(LEDData_MessageType_HSV_DATA): 
        set_main_rgb_value_hsv(next_led_data.kelvin_red_hue, next_led_data.green_saturation, next_led_data.blue_value); 
        break; 

        default: 
        break; 
    }    
    LEDMessageSignal.clear(THREAD_SIGNAL_0); 
    
    os_thread_delay_ms(6);
}
