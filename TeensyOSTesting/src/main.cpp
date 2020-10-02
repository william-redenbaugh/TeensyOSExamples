#include <Arduino.h>
#include "OS/OSThreadKernel.h"

void setup() {
  os_init(); 

  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  os_thread_delay_s(1); 
  digitalWrite(LED_BUILTIN, LOW); 
  os_thread_delay_s(1); 
   
}