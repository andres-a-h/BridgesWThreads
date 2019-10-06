# BridgesWThreads

## 1. Usage
    [Usage] ./test
    make sure to 'make' before executing

## 2. Assumptions
- The user defines variables with proper values in 'handlecar.h'.
- I also assumed that the user does not create more threads than allowable in memory before they start overwriting
- The user enters 'TO_HANOVER' or 'TO_NORWICH' for the direction for the 'OneVehicle()' function argument

## 3. Testing
Although the makefile does not include multiple testing conditions, the user can change the testing conditions inside 'main()' in 'traffic.c'. However, I did conduct different tests on the program. They are as follows:
- I started small, only creating one car (thread) going to Hanover and one car going to Norwich to ensure that they would not crash
- I interleaved the creation of threads. Because directions are starved, whichever direction first obtained the lock would be the direction that would get the bridge. The other direction would have to wait until the bridge was empty before attempting to obtain the lock.
- I interleaved the creation of threads, then I slept main() for 5 seconds then created 10 threads going the opposite direction of the last direction traveled and another 10 going the other direction. I did this so that I can ensure that if a car is waiting for the bridge to clear (of cars going to Hanover) in order to cross, then it would actually cross to Norwich once the bridge was empty
- NOTE: feel free to modify 'main()' to any testing configuration desired. One creates a thread as follows: `pthread_create(&threadID, NULL, OneVehicle, (void *)direction'`

## 4. Limitations
- Directions can be starved if the cars going the other direction keep showing up. However, a method that could fix this would be to include a "stoplight" that stop flow of traffic in one direction after some time or x amount of cars pass through
- The program isn't surprisingly fast as I've included a sleep(time) in the 'OnBridge(direction)' function. I did this because without it, it is rather difficult to make sure more than 1 car is on the bridge at any given time. By sleeping the thread for x amount of time (I chose 1 second), we can represent a moderate speed for the cars that will allow multiple cars on the bridge because they are not going so fast.
