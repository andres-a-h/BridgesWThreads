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
#include <stdint.h>
#include <stdbool.h>
#include "handlecar.h"

pthread_t car[NUM_THREADS];
int rc;
int active = 0; // number of cars currently on the Bridge
int waiting = 0; // number of cars waiting
bool safeToHanover = true; // determines if it is safe to cross to Hanover
bool safeToNorwich = true; // determines if it is safe to cross to Norwich
pthread_mutex_t lock; // the lock
pthread_cond_t cond, cond2; // condition variable

int main(int argc, char *argv[]) {


    // create a mutex lock - return error if it fails
    if (pthread_mutex_init(&lock, NULL) != 0) {
        fprintf(stderr, "\n Error: Mutex creation failed!\n");
        return 1;
    }
    // create condition variable - return error if it fails
    if (pthread_cond_init(&cond, NULL) != 0) {
        fprintf(stderr, "\n Error: Conditional Variable creation failed!\n");
        return 2;
    }

    // create a thread for each car alternating where cars are headed
    for (int i = 0; i < NUM_THREADS; i++) {
        fprintf(stdout, "=====> main() : a car is arriving at the bridge! (creating thread) <=====\n");
        waiting++; // add to waiting list of cars

        if (i % 2 == 0) {
            rc = pthread_create(&car[i], NULL, OneVehicle, (void *) TO_HANOVER);
        }
        else {
            rc = pthread_create(&car[i], NULL, OneVehicle, (void *) TO_NORWICH);
        }

        if (rc) { // if thread creation fails
            fprintf(stdout, "Error: could not create thread! rc = %d\n", rc);
            waiting--;
            exit(-1);
        }
    }

    pthread_exit(NULL);

    return 0;
}
