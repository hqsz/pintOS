#ifndef THREADS_INIT_H
#define THREADS_INIT_H

#include <debug.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Page directory with kernel mappings only. */
extern uint32_t *init_page_dir;

#endif /* threads/init.h */

/*
  2017.11.12
    thread
      Modify thread_yield / thread_unblock(using FIFO -> priority scheduling)

  2017.11.13
    thread
      Modify thread_set_priority / thread_create(preemtion by priority)
    sync
      Modify sema_up / sema_down(using FIFO -> priority scheduling)

  2017.11.16
    thread
      Add member for alarm-clock to thread struct
    ../devices/timer
      Modify timer_sleep / timer_interrupt(busy waiting -> alarm-clock) > no more inequality please.. end with 11.17

  2017.11.18
    thread
      Add thread aging to thread_tick(aging thread in ready list periodically) > Let's additional requirement
      Add member for 4.4BSD scheduler to thread struct / global variable for 4.4 BSD scheduler
    lib/stdfloat
      Define fixed-point real arithmetic data type / operations

  2017.11.19
    thread
      Implement thread_get_recent_cpu / thread_get_load_avg
    ../Makefile 
      Add stdfloat library to pintos make option

  2017.11.20
    thread
      Add update priority / recent_cpu / load_avg > why mlfqs-load-1 fail.. 
      Modify thread_set_nice(recalculate thread priority / preemtion by priority)
      Modify calculate ready_threads > ALL PASS !! shall we donate?.. maybe next time..
*/
