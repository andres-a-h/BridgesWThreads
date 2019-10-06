#ifndef HANDLECAR_H_
#define HANDLECAR_H_

// forward-declare vars
extern pthread_mutex_t lock; // source: https://stackoverflow.com/questions/37083224/how-to-define-pthread-and-mutex-lock-in-c-files-that-depend-on-each-other
extern pthread_cond_t cond;
extern bool safe;
extern int active;
extern int waiting;

// define const vars
#define MAX_CARS 3
#define NUM_THREADS 10
#define TO_HANOVER 0
#define TO_NORWICH 1

/* function for thread in charge of handling a single car */
void *OneVehicle(void *direction);

/* ArriveBridge(): helper function that does not return until safe to get on bridge */
void ArriveBridge(void *direction);

/* OnBridge(): helper function prints state of bridge and waiting cars */
void OnBridge(void *direction);

/* ExitBridge(): helper function removes the car from the bridge */
void ExitBridge(void *direction);

#endif // HANDLECAR_H_
