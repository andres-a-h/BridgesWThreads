/**
* @author: Andres Hernandez, Dartmouth College, CS 58
* @date: Fall 2019
**/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "handlecar.h"

#define MAX_CARS 3
#define TO_HANOVER 1
#define TO_NORWICH 2

int main(int argc, char *argv[]) {

  pthread_t car1, car2;
  OneVehicle(TO_HANOVER);

  return 0;
}
