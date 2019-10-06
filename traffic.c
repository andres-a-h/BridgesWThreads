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

#define MAX_CARS 3
#define TO_HANOVER 0
#define TO_NORWICH 1

int active = 0; // number of cars currently on the Bridge
bool safe = true; // determines whether it is safe to cross the bridge
pthread_mutex_t lock; // the lock
pthread_cond_t cond; // condition variable

int main(int argc, char *argv[]) {

    pthread_t car[MAX_CARS];
    int rc;

    // create a mutex lock - return error if it fails
    if (pthread_mutex_init(&lock, NULL) != 0) {
        fprintf(stderr, "\n Error: Mutex creation failed!\n");
        return 1;
    }
    // create condition variable - return error if it fails
    if (pthread_cond_t(&cond, NULL) != 0) {
        fprintf(stderr, "\n Error: Conditional Variable creation failed!\n");
        return 2;
    }

    // create a thread for each car
    for (int i = 0; i < MAX_CARS; i++) {
        fprintf(stdout, "====> main() : creating thread\n");
        rc = pthread_create(&car[i], NULL, OneVehicle, (void *) TO_HANOVER);

        if (rc) { // if thread creation fails
            fprintf(stdout, "Error: could not create thread! rc = %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);

    return 0;
}
