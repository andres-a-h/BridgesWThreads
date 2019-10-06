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
    unsigned int dir = (uintptr_t) direction;

    // wait until we are safely able to attempt to cross the bridge to Hanover
    while ((!safeToHanover && (dir == TO_HANOVER)) || active >= MAX_CARS) {
        pthread_cond_wait(&cond, &lock);
    }
    // wait until we are safely able to attempt to cross the bridge to Norwich
    while ((!safeToNorwich && (dir == TO_NORWICH)) || active >= MAX_CARS) {
        pthread_cond_wait(&cond2, &lock);
    }

    if (dir == TO_HANOVER) { // car is going to Hanover
        fprintf(stdout, "\t++++++++++> I am car %d, and I am entering the bridge going to Hanover!\n", pthread_self());
        safeToNorwich = false; // not safe to go to Norwich
    }
    else { // car is going to Norwich
        fprintf(stdout, "\t++++++++++> I am car %d, and I am entering the bridge going to Norwich!\n", pthread_self());
        safeToHanover = false; // not safe to go to Hanover
    }


    // do whatever we need to do, enter the bridge!
    active++; // increment number of cars currently on the bridge
    waiting--; // car enters bridge, decrementing amount of waiting cars

    // release the lock once we are done with it
    pthread_mutex_unlock(&lock);
}

/* OnBridge(): helper function prints state of bridge and waiting cars */
void OnBridge(void *direction) {
    // obtain lock to securely check state of bridge
    // we do not want variables to change before we can report to user
    //pthread_mutex_lock(&lock);

    sleep(1); // make sure cars don't travel so fast that other cars can't get on at same time
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

    // if the bridge is empty, then it is safe for either to cross
    if (active == 0) {
        safeToHanover = true;
        safeToNorwich = true;
    }

    // wakeup at least one thread that are waiting to enter Bridge
    if (direction == TO_HANOVER) {
        pthread_cond_signal(&cond);
    }
    else {
        pthread_cond_signal(&cond2);
    }
    // release
    pthread_mutex_unlock(&lock);
}
