#include "rgb_runtime_thread.hpp"

#define LED_MATRIX_RUNTIME_STACK_SIZE 1024
static uint32_t rgb_runtime_stack[LED_MATRIX_RUNTIME_STACK_SIZE];
#undef LED_MATRIX_RUNTIME_STACK_SIZE

void start_rgb_runtime_thread(void); 
static void rgb_runtime_thread(void *parameters); 
static inline void rgb_loop(void); 
static inline void rgb_setup(void); 

void start_rgb_runtime_thread(void){
    os_add_thread(&rgb_runtime_thread, NULL, sizeof(rgb_runtime_stack), rgb_runtime_stack);  
}

static void rgb_runtime_thread(void *parameters){
    rgb_setup(); 
    for(;;)
        rgb_loop(); 
}

static inline void rgb_loop(void){
    os_thread_delay_s(1); 
    HsvColor random_col = {random(255), 255, 255}; 
    fade_main_hsv(random_col, 1);  
}

static inline void rgb_setup(void){
    setup_rgb_led_gpio();  
}