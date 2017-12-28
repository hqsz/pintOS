#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);

#endif /* userprog/process.h */

/*
	2017.9.30 ~ 10.3
		Pintos manual reading...

	2017.10.4
		process
			Before filesys_open add parsing command
			Change arguments file_name to argv[0] (parsed command)
			After setup_stack add push arguments 
			cf) memcpy -> move contents, '=' -> move address > fucking 4 hours
			Write hex_dump for debugging

	2017.10.5
		process
			Confirm hex_dump value is clear
		syscall
			Find f->esp value is system call number and parameters / f->eax is place of return value

	2017.10.6
		exception
			User memory access exception handling
	
	2017.10.7
		process
			Add parsing file_name for exit message
		../lib/syscall-nr
			Add SYS_PIBONACCI / SYS_SUMOFFOURINT
		syscall
			Add pibonacci / sum_of_four_integers
		../lib/user/syscall
			Add pibonacci / sum_of_four_integers / syscall4
		../examples/sum
			Make example file for additional system call
			cf) syscall4(syscall_num, ...) > atoi is start at 1, not 0 > fucking 8 hours
		../examples/Makefile
			Modify Makefile for add complie sum.c

	2017.10.8
		syscall
			Add system call infrastructure but not clear(passing parameter order is 1,2..???) > Maybe complete..
			Complete halt / write (only stdout) / read (only stdin)

	2017.10.9
		../threads/thread
			Add member for relationship to thread struct
    syscall
      Complete exec / wait / exit only but not pass

  2017.10.10
    UnderStand synchronization / blocking / semaphore ...

  2017.10.11
    process
      Complete wait and exit > starting at 18 pass
      Tuning for exec-missing(checking filesys_open)
      Tuning for wait-twice(remove finish child in list) > ALL PASS !!!
    syscall
      Tuning for sc-bad-args(checking argument address) 

  2017.10.13
    Modify code more efficiently
    Write Doument.hwp

  2017.10.30
    syscall
      Add system call infrastructure
      No more ctrl-c and ctrl-v > fucking 4 hours (only left 12 testcase)
      Tuning for open-missing(checking filesys_open)
      Tuning for close-twice(modify system call close)
      Tuning for create-null and open-null(checking string argument)
    ../threads/thread
      Modify thread member for relationship and Add member for file system

    2017.10.31
      syscall
        Tuning for read-bad-ptr(modify is_unvalid_vaddr)
    
    2017.11.06
      process
        Add synchronization between parent and child at loading child > success syn series.. god demn..
      syscall
        Add global semaphore for synchronize file read/write/open
        Add file_deny_write to open system call
      ../threads/thread
        Add is_open_file > success rox series..
  
    2017.11.08
      ../threads/thread
        Add flag checking whether load is success
      process
        Modify Tuning for exec-missing(if load fail, remove child from parent child list); > MULTI OOM !!!! finish.. jesus christ..
        
*/
