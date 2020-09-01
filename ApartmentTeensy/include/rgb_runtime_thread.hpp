#ifndef _RGB_RUNTIME_THREAD_HPP
#define _RGB_RUNTIME_THREAD_HPP

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

// Our Master Light Manipulation library. 
#include "rgb_master_light.hpp"

void start_rgb_runtime_thread(void); 

#endif 