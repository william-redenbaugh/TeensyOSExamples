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

#include "rgb_runtime_thread.hpp"

void setup() {
  // Macro that initializes the primary thread. 
  os_init();
  // Setup low priority thread. 
  setup_lwip_thread();
  // Starts up the OS managed serial interface. 
  os_usb_serial_begin();
  // Sets up our message callback thread  
  message_callbacks_begin();  
  // Sets up our rgb runtime environment 
  start_rgb_runtime_thread(); 
}

void loop() {
  os_thread_delay_s(1);   
}