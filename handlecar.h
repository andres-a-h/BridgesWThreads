#ifndef HANDLECAR_H_
#define HANDLECAR_H_

/* function for thread in charge of handling a single car */
void OneVehicle(int direction);

/* ArriveBridge(): helper function that does not return until safe to get on bridge */
void ArriveBridge(int direction);

/* OnBridge(): helper function prints state of bridge and waiting cars */
void OnBridge(int direction);

/* ExitBridge(): helper function removes the car from the bridge */
void ExitBridge(int direction);

#endif // HANDLECAR_H_
