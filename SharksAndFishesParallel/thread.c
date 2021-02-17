#include "header.h"

void populateOcean();
void printPopulation();
void checkNeighbors();
void fishBirth();
void sharkBirth();
void fishEaten();
void growth();
void death();
void copyOcean();
void movement();

//For looping.
int x=0, y=0, runCount=250;

pthread_mutex_t lock;

void *threadFunction(void *rank){

  srand(time(NULL));

  //Will cause the thread to wait until no other thread is in the critical section.
  pthread_mutex_lock(&lock);  

  for (int i = 0; i < runCount; i++) {
    //Copy the ocean.
    copyOcean();

    //Show ocean.
    printPopulation();
    
    //START RUN-------------------------------------
    for (x = 0; x < oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            checkNeighbors(x, y);
            fishEaten(x, y);
            fishBirth(x, y);
            sharkBirth(x, y);
        }
    }
  
    growth();
    death();
    movement();
  }
  //END RUN----------------------------------------

  //Notifies the system that the calling thread has completed execution of the code in the critical section.
  pthread_mutex_unlock(&lock);
 
  
  return NULL;
  //threadFunction
}