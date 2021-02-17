//Lin Yuan Chong
//Conor Cassidy
//Zygimantas Gaubas
//Flaviu Cuc

#include "header.h"

//Declare functions.
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
//Declare thread function.
void *threadFunction(void *rank);

//Declare variables.
const int maxThreads = 64;
int threadCount = 4;

pthread_mutex_t lock;

//MAIN METHOD.
int main() {

  //Populate the ocean.
  populateOcean();
  //64 bits system
  long thread;

  //Intialises the lock mutex.
  pthread_mutex_init(&lock, NULL);

  pthread_t thread_handles[threadCount];

  //Creating thread_count quantity of threads.
  for (thread = 0; thread < threadCount; thread++) {
    pthread_create(&thread_handles[thread], NULL, threadFunction, (void*) thread);
  }
  

  //Joining all threads i.e. waiting for all threads to complete.
  for (thread = 0; thread < threadCount; thread++) {
    pthread_join(thread_handles[thread], NULL);
  }

  //To store execution time of code.
  double time_spent = 0.0;

  clock_t begin = clock();

  //Wait.
  sleep(3);

  clock_t end = clock();

  //Calculate elapsed time by finding difference (end - begin) and dividing the difference by CLOCKS_PER_SEC to convert to seconds.
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Time elapsed is %f seconds", time_spent);

  pthread_mutex_destroy(&lock);

  return 0;
  
}