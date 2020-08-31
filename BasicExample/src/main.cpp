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

#define RED_GPIO   2
#define GREEN_GPIO 3
#define BLUE_GPIO  4

void setup() {
  // Macro that initializes the primary thread. 
  os_init();
  // Setup low priority thread. 
  setup_lwip_thread();
  // Starts up the OS managed serial interface. 
  os_usb_serial_begin();
  

  analogWriteResolution(12); 
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  analogWriteFrequency(2, 36621.09);
  analogWriteFrequency(3, 36621.09);
  analogWriteFrequency(4, 36621.09);

  analogWrite(2, 100);
  analogWrite(3, 100); 
  analogWrite(4, 100);
  
  message_callbacks_begin();  
}

void loop() {
  os_thread_delay_s(1);   
}