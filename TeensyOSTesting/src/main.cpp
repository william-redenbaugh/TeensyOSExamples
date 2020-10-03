#include <Arduino.h>
#include "OS/OSThreadKernel.h"

// Thread handler ID that we can use to manipulate a thread. 
os_thread_id_t target_thread; 

// Function that we are spawning with our thread. 
void example_thread(void *parameters){
  while(1){
    // Delays a thread for 100 milliseconds    
    os_thread_delay_ms(100);
  }
}

void setup(){
  os_init();
  // Instanciate the thread with the given thread ID if we want to instruct it later. 
  target_thread = os_add_thread((thread_func_t)example_thread, 0, -1, 0);
}

void loop(){
  os_thread_delay_ms(100);
}