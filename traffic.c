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

#define MAX_CARS 3
char *direction;

/* function for thread in charge of handling a single car */
void OneVehicle(char *direction) {
  ArriveBridge(direction);
  // now the car is on the Bridge

  OnBridge(direction);

  ExitBridge(direction);
  // now the car is off the Bridge
}

/* ArriveBridge(): helper function that does not return until safe to get on bridge */
void ArriveBridge(char *direction) {
  fprintf(stdout, "I am getting on the bridge\n");
}

/* OnBridge(): helper function prints state of bridge and waiting cars */
void OnBridge(char *direction) {
  fprintf(stdout, "I am the only car on the bridge\n");
}

/* ExitBridge(): helper function removes the car from the bridge */
void ExitBridge(char *direction) {
    fprintf(stdout, "I am exiting the bridge\n");
}

int main(int argc, char *argv[]) {

  pthread_t car1, car2;

  OneVehicle(TO_HANOVER);

  return 0;
}
