#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "lib/stdio.h"

void syscall_init(void);

/* Process identifier. */
typedef int pid_t;

/* System call. */
#define halt() shutdown_power_off()
void exit(int status);
pid_t exec(const char *cmd_line);
int wait(pid_t pid);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);

bool create(const char *file, unsigned initial_size);
bool remove(const char *file);
int open(const char* file);
int filesize(int fd);
void seek(int fd, unsigned position);
unsigned tell(int fd);
void close(int fd);

/* Additonal System call. */
int pibonacci(int n);
int sum_of_four_integers(int a, int b, int c, int d);

/* Check user address exception. Tuning for sc-bad-arg. */
void is_unvalid_vaddr(uintptr_t *vaddr, int count);

/* Check string value exception. Tuning for create-null and open-null. */
void is_unvalid_string(const char *string);

#endif /* userprog/syscall.h */
