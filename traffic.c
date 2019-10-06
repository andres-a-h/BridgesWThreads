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
#include "handlecar.h"

#define MAX_CARS 3
#define NUM_THREADS 3
#define TO_HANOVER 0
#define TO_NORWICH 1

int main(int argc, char *argv[]) {

    pthread_t car[NUM_THREADS];
    int rc;
    for (int i = 0; i < NUM_THREADS; i++) {
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
