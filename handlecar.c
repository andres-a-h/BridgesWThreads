#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include "handlecar.h"

/* function for thread in charge of handling a single car */
void *OneVehicle(void *direction) {
    unsigned int dir = (uintptr_t) direction; // source: https://stackoverflow.com/questions/26805461/why-do-i-get-cast-from-pointer-to-integer-of-different-size-error
    sleep(3);
    ArriveBridge(direction);
    // now the car is on the Bridge

    OnBridge(direction);

    ExitBridge(direction);
    // now the car is off the Bridge

    return NULL;
}

/* ArriveBridge(): helper function that does not return until safe to get on bridge */
void ArriveBridge(void *direction) {
    // obtain the lock if possible
    pthread_mutex_lock(&lock);

    // wait until we are safely able to attempt to cross the bridge
    while (!safe || active > 3) {
        pthread_cond_wait(&cond, &lock);
    }

    // do whatever we need to do, enter the bridge!
    active++; // increment number of cars currently on the bridge
    waiting--; // car enters bridge, decrementing amount of waiting cars
    fprintf(stdout, "\t++++++++++> I am car %d, and I am entering the bridge!\n", pthread_self());

    // release the lock once we are done with it
    pthread_mutex_unlock(&lock);
}

/* OnBridge(): helper function prints state of bridge and waiting cars */
void OnBridge(void *direction) {
    // obtain lock to securely check state of bridge
    // we do not want variables to change before we can report to user
    //pthread_mutex_lock(&lock);

    sleep(2); // make sure cars don't travel so fast that other cars can't get on at same time
    fprintf(stdout, "\t I am car %d, here is the current state of the bridge:\n", pthread_self());
    fprintf(stdout, "\t\t Cars on bridge: %d\n\t\t Cars waiting: %d\n", active, waiting);

    // release lock now that we are done checking
    //pthread_mutex_unlock(&lock);
}

/* ExitBridge(): helper function removes the car from the bridge */
void ExitBridge(void *direction) {
    // obtain lock to ensure exclusive access to vars
    pthread_mutex_lock(&lock);

    active--; // car leaves bridge, so no longer active
    fprintf(stdout, "\t----------> I am car %d, and I am exiting the bridge!\n\n", pthread_self());

    // wakeup at least one thread that are waiting to enter Bridge
    pthread_cond_signal(&cond);

    // release
    pthread_mutex_unlock(&lock);
}
