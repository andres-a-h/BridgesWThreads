#include "handlecar.h"

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
