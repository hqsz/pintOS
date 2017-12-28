#include <stdio.h>
#include <syscall.h>
#include <stdlib.h>
#include "../lib/user/syscall.h"

int
main (int argc, char **argv)
{
  int arr[4];

  arr[0] = atoi(argv[1]);
  arr[1] = atoi(argv[2]);
  arr[2] = atoi(argv[3]);
  arr[3] = atoi(argv[4]);

	printf("%d %d\n", pibonacci(arr[0]), sum_of_four_integers(arr[0],arr[1],arr[2],arr[3]));

  return EXIT_SUCCESS;
}
