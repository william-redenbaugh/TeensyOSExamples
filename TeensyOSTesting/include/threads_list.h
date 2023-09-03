#ifndef _THREADS_LIST_H
#define _THREADS_LIST_H
#include "global_includes.h"
#include "test_module.h"
const task_init_descriptor_t INIT_THREAD_LIST[] =
    {
        {test_module_thread, test_module_init, "Test module", 4096, NULL, 0, NULL},
};
extern int NUM_THREADS;
#endif