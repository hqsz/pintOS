#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "threads/vaddr.h"
#include "devices/input.h"
#include "lib/kernel/stdio.h"

#include "userprog/process.h"
#include "filesys/file.h"
#include "filesys/filesys.h"

static void syscall_handler (struct intr_frame *);

struct semaphore mutex;

	void
syscall_init (void) 
{
  sema_init(&mutex, 1); 

	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

/* System call infrastructure. Execute proper system call by stack.
   Checking stack address before passing argument to system call. */
	static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	/* Caller's stack pointer. */
	uintptr_t* param = f->esp;
    
#ifdef DEBUG
	hex_dump((uintptr_t)param, (const char *)param, (uintptr_t)PHYS_BASE - (uintptr_t)param, true);
#endif	

	/* System call number is first argument in caller's stack pointer. 
	 	 Return values is placed in eax register. */
	
  switch(param[0]){
		case SYS_HALT:
      is_unvalid_vaddr(param, 1);
			halt();
			break;
		case SYS_EXIT:
      is_unvalid_vaddr(param, 2);
			exit(param[1]);
			break;
		case SYS_EXEC:
      is_unvalid_vaddr(param, 2);
			f->eax = exec((const char *)param[1]);
			break;
		case SYS_WAIT:
      is_unvalid_vaddr(param, 2);
			f->eax = wait(param[1]);
			break;
		case SYS_READ:
      /* Tuning for read-bad-ptr. */
      is_unvalid_vaddr(param, 4);
			f->eax = read(param[1], (void *)param[2], param[3]);
			break;
		case SYS_WRITE:
      is_unvalid_vaddr(param, 4);
			f->eax = write(param[1], (const char *)param[2], param[3]);
			break;
		case SYS_PIBONACCI:
      is_unvalid_vaddr(param, 2);
			f->eax = pibonacci(param[1]);
			break;
		case SYS_SUMOFFOURINT:
      is_unvalid_vaddr(param, 5);
			f->eax = sum_of_four_integers(param[1], param[2], param[3], param[4]);
			break;
    
    case SYS_CREATE:
      is_unvalid_vaddr(param, 3);
      f->eax = create((const char *)param[1], param[2]);
      break;
    case SYS_REMOVE:
      is_unvalid_vaddr(param, 2);
      f->eax = remove((const char *)param[1]);
      break;
    case SYS_OPEN:
      is_unvalid_vaddr(param, 2);
      f->eax = open((const char *)param[1]);
      break;
    case SYS_FILESIZE:
      is_unvalid_vaddr(param, 2);
      f->eax = filesize(param[1]);
      break;
    case SYS_SEEK:
      is_unvalid_vaddr(param, 2);
      seek(param[1], param[2]);
      break;
    case SYS_TELL:
      is_unvalid_vaddr(param, 2);
      f->eax = tell(param[1]);
      break;
    case SYS_CLOSE:
      is_unvalid_vaddr(param, 2);
      close(param[1]);
      break;

	}

#ifdef DEBUG
	intr_dump_frame(f);
#endif

}

/* System call. */

/* Terminate current program by thread_exit. Print process termination message.  
   Returning status to thread struct(kernel). */
void exit(int status){
  struct thread *cur = thread_current();

  cur->exit_status = status;
  printf("%s: exit(%d)\n", cur->name, status);
	thread_exit();
}

/* Run process whose name is cmd_line by process_execute. */
pid_t exec(const char *cmd_line){
	return process_execute(cmd_line);
}

/* Wait child process whose pid is pid by process_wait. */
int wait(pid_t pid){
	return process_wait(pid);
}

/* Read size bytes from the file open as fd into buffer.
   In project 2_1, only implement STDIN. */
int read(int fd, void *buffer, unsigned size){
	unsigned i;
  int ret;
  struct thread *cur = thread_current();

  sema_down(&mutex);
  if(fd == STDIN_FILENO){
		for(i = 0; i < size; i++){ 
			((uint8_t *)buffer)[i] = input_getc();
		}
    ret = size;
	}
	else{
    ret = file_read(cur->file[fd], buffer, size);
  }
  sema_up(&mutex);
  return ret;
}

/* Write size bytes form buffer to file open ad fd.
   In proejct 2_1, only implement STDOUT. */
int write(int fd, const void *buffer, unsigned size){
  int ret;
  struct thread *cur = thread_current();
  
  sema_down(&mutex);
  if(fd == STDOUT_FILENO){
		putbuf(buffer, size);
		ret = size;
	}
  else{
    ret = file_write(cur->file[fd], buffer, size);
  }
  sema_up(&mutex);
  return ret;
}

bool create(const char *file, unsigned initial_size){
  /* Tuning for create-null. */
  is_unvalid_string(file);
  return filesys_create(file, initial_size);
}

bool remove(const char *file){
  return filesys_remove(file);
}

int open(const char *file){
  int i;
  int ret = -1;
  struct thread *cur = thread_current();

  is_unvalid_string(file);

  sema_down(&mutex);
  struct file *open = filesys_open(file);

  /* Read only executable file. */
  if(is_open_file(file)){
    file_deny_write(open);
  }

  /* Tuning for open-missing. */
  if(open){
    for(i = 2; i < 130; i++){
      if(!(cur->file[i])) {
        cur->file[i] = open;
        ret = i;
        break;
      }
    }
  }
  sema_up(&mutex);
  return ret;
}

int filesize(int fd){
  return file_length(thread_current()->file[fd]);
}
  
void seek(int fd, unsigned position){
  file_seek(thread_current()->file[fd], position);
}

unsigned tell(int fd){
  return file_tell(thread_current()->file[fd]);
}

void close(int fd){
  struct thread *cur = thread_current();

  file_close(cur->file[fd]);
  /* Tuning for close-twice. */
  cur->file[fd] = NULL;
}

/* Additonal system call. */

/* Return n'th fibonacci number. */
int pibonacci(int n){
	int a = 1, b = 1;
	int i;

	for(i = 1; i < n; i++){
		a += b;
		b = a-b;
	}
	return a;
}

/* Return sum of four integers. */
int sum_of_four_integers(int a, int b, int c, int d){
	return a+b+c+d;
}

/* Check user address exception. Tuning for sc-bad-arg. */
void is_unvalid_vaddr(uintptr_t *vaddr, int count){
  int i;

  for(i = 0; i < count; i++){
    if(is_kernel_vaddr((const void *)vaddr[i])){
      exit(-1);
      break;
    }
  }
}

/* Check string value exception. Tuning for create-null and open-null. */
void is_unvalid_string(const char *string){
  if(!string) exit(-1);
}
