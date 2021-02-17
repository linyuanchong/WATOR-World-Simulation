#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define oceanSize 10

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

//For looping
int x=0, y=0,
runCount = 1000,
//For passing.
    i, j,
    randomNum, randomNumCap=10,
    ocean[oceanSize][oceanSize],
    oceanCopy[oceanSize][oceanSize],
    fish, 
    shark, 
    emptyCell, 
    parallelFish, 
    parallelShark, 
    parallelEmptyCell, 
    ageFish,
    ageShark,
    generations,
    tFishC, tSharkC, bFishC, mFishC, bSharkC, mSharkC, emptyNeighborC,
    fishCount, sharkCount;
int parallelOcean[oceanSize][oceanSize];


//MAIN METHOD.
int main() {
    
  srand(time(NULL));
  
  //Populate the ocean.
  populateOcean();

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
  
  //To store execution time of code.
  double time_spent = 0.0;

  clock_t begin = clock();

  //Wait.
  sleep(3);

  clock_t end = clock();

  //Calculate elapsed time by finding difference (end - begin) and dividing the difference by CLOCKS_PER_SEC to convert to seconds.
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Time elapsed is %f seconds", time_spent);

  return 0;
}

void populateOcean() {
    x =0;
    y = 0;
    for(x = 0; x < oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            randomNum = (rand() % randomNumCap);
            //Empty.
            if(randomNum==0){
                emptyCell += 1;
                ocean[x][y] = 0;
            }
            //Fish.
            else if(randomNum>=1 && randomNum<=5) {
                fish += 1;
                ocean[x][y] = randomNum;
            } 
            //Shark.
            else if(randomNum>=6 && randomNum<=10) {
                shark += 1;
                ocean[x][y] = randomNum;
            }
        }
    }

  printf("\n\n____________________________________________\n\n");
  printf("BEGINNING DATA:\n");
  printf("Total number of fishes: %d \n", fish);
  printf("Total number of sharks: %d \n", shark);
  printf("Total number of empty cells: %d \n", emptyCell);
  printf("____________________________________________");
}

//Ocean environment printing.
void printPopulation() {
    x=0,y=0;
    
    printf("\n\n");
    
    for(x=0; x<oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            if (y < oceanSize) {
                printf("%d", ocean[x][y]);
            }
        } printf("\n");
    }
    printf("\n____________________________________________\n");
}

void movement() {
    x=0,y=0;
    
    for(x=0; x<oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            if (y < oceanSize) {
                ocean[x][y] = oceanCopy[x][(y+oceanSize-1)%oceanSize];
            }
        }
    }
    
}

//Copy ocean.
void copyOcean() {
    x=0,y=0;
    
    for(x=0; x<oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            if (y < oceanSize) {
                oceanCopy[x][y] = ocean[x][y];
            }
        }
    }
    
}

//Neighbor checking.
void checkNeighbors(i, j) {
    
    //North neighbor.
    if (ocean[(i+oceanSize-1)%oceanSize][j] >=1 && ocean[(i+oceanSize-1)%oceanSize][j]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if(ocean[(i+oceanSize-1)%oceanSize][j]>=4 && ocean[(i+oceanSize-1)%oceanSize][j]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize-1)%oceanSize][j]>=6 && ocean[(i+oceanSize-1)%oceanSize][j]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize-1)%oceanSize][j]>=9 && ocean[(i+oceanSize-1)%oceanSize][j]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize-1)%oceanSize][j]==0) {
        emptyNeighborC += 1;
    }
    
    //South neighbor.
    if (ocean[(i+oceanSize+1)%oceanSize][j]>=1 && ocean[(i+oceanSize+1)%oceanSize][j]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if(ocean[(i+oceanSize+1)%oceanSize][j]>=4 && ocean[(i+oceanSize+1)%oceanSize][j]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize+1)%oceanSize][j]>=6 && ocean[(i+oceanSize+1)%oceanSize][j]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize+1)%oceanSize][j]>=9 && ocean[(i+oceanSize+1)%oceanSize][j]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize+1)%oceanSize][j]==0) {
        emptyNeighborC += 1;
    }
    
    //East neighbor.
    if (ocean[i][(j+oceanSize+1)%oceanSize]>=1 && ocean[i][(j+oceanSize+1)%oceanSize]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if (ocean[i][(j+oceanSize+1)%oceanSize]>=4 && ocean[i][(j+oceanSize+1)%oceanSize]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[i][(j+oceanSize+1)%oceanSize]>=6 && ocean[i][(j+oceanSize+1)%oceanSize]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[i][(j+oceanSize+1)%oceanSize]>=9 && ocean[i][(j+oceanSize+1)%oceanSize]<=10) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[i][(j+oceanSize+1)%oceanSize]==0) {
        emptyNeighborC += 1;
    }
    
    //West neighbor.
    if (ocean[i][(j+oceanSize-1)%oceanSize]>=1 && ocean[i][(j+oceanSize-1)%oceanSize]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if (ocean[i][(j+oceanSize-1)%oceanSize]>=4 && ocean[i][(j+oceanSize-1)%oceanSize]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[i][(j+oceanSize-1)%oceanSize]>=6 && ocean[i][(j+oceanSize-1)%oceanSize]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[i][(j+oceanSize-1)%oceanSize]>=9 && ocean[i][(j+oceanSize-1)%oceanSize]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[i][(j+oceanSize-1)%oceanSize]==0) {
        emptyNeighborC += 1;
    }
    
    //Northwest neighbor.
    if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]>=1 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]>=4 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]>=6 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]>=9 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize]==0) {
        emptyNeighborC += 1;
    }
    
    //Southwest neighbor.
    if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]>=1 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]>=4 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]>=6 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]>=9 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize]==0) {
        emptyNeighborC += 1;
    }
    
    //Northeast neighbor.
    if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]>=1 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if(ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]>=4 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]>=6 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]>=9 && ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize] == 0) {
        emptyNeighborC += 1;
    }
    
    //Southeast neighbor.
    if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]>=1 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]<=3) {
        bFishC += 1;
        tFishC += 1;
    }
    else if(ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]>=4 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]<=5) {
        mFishC += 1;
        tFishC += 1;
    }
    else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]>=6 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]<=8) {
        bSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]>=9 && ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize]<=10) {
        mSharkC += 1;
        tSharkC += 1;
    }
    else if(ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize] == 0) {
        emptyNeighborC += 1;
    }
    
    //Print results.
    //printf("\n\nChecking for cell: %d, %d (%d)\n", i, j, ocean[i][j]);
    //printf("Total of fish neighbors: %d \n", tFishC);
    //printf("Total of shark neighbors: %d \n", tSharkC);
    //printf("Number of baby fish neighbors: %d \n", bFishC);
    //printf("Number of mature fish neighbors: %d \n", mFishC);
    //printf("Number of baby shark neighbors: %d \n", bSharkC);
    //printf("Number of mature shark neighbors: %d \n", mSharkC);
    //printf("Number of empty neighbors: %d ", emptyNeighborC);
    
}

//Fish breeding.
void fishBirth(i, j) {

    //If cell is fish.
    if (ocean[i][j]>=4 && ocean[i][j] <= 5) {
        //If surrounded by 3 fishes(at least), fishes breed.
        if (mFishC>=2 && emptyNeighborC>=1) {
            printf("\n\nFish slot available. \n");
                //North empty.
                if (ocean[(i+oceanSize-1)%oceanSize][j] == 0) {
                    //printf("north empty");
                    ocean[(i+oceanSize-1)%oceanSize][j] = 1;
                }
                //South empty.
                else if (ocean[(i+oceanSize+1)%oceanSize][j] == 0) {
                    //printf("south empty");
                    ocean[(i+oceanSize+1)%oceanSize][j] = 1;
                }
                //East empty.
                else if (ocean[i][(j+oceanSize+1)%oceanSize] == 0) {
                    //printf("east empty");
                    ocean[i][(j+oceanSize+1)%oceanSize] = 1;
                }
                    //West empty.
                else if (ocean[i][(j+oceanSize-1)%oceanSize] == 0) {
                    //printf("west empty");
                    ocean[i][(j+oceanSize-1)%oceanSize] = 1;
                }
                    //Northwest empty.
                else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize] == 0) {
                    //printf("northwest empty");
                    ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize] = 1;
                }
                    //Southwest empty.
                else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize] == 0) {
                    //printf("southwest empty");
                    ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize] = 1;
                }
                    //Northeast empty.
                else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize] == 0) {
                    //printf("northeast empty");
                    ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize] = 1;
                }
                    //Southeast empty.
                else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize] == 0) {
                    //printf("southeast empty");
                    ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize] = 1;
                }
        }
    }
}

//Shark breeding.
void sharkBirth(i, j) {
    
    //If cell is shark.
    if (ocean[i][j] >= 9 && ocean[i][j] <= 10) {
        //If surrounded by 4 sharks(at least), sharks breed.
        if (mSharkC>=4 && emptyNeighborC>=1) {
            //printf("\n\nShark slot available.\n");
                //North empty.
                if (ocean[(i+oceanSize-1)%oceanSize][j] == 0) {
                    //printf("north empty");
                    ocean[(i+oceanSize-1)%oceanSize][j] = 2;
                }
                //South empty.
                else if (ocean[(i+oceanSize+1)%oceanSize][j] == 0) {
                    //printf("south empty");
                    ocean[(i+oceanSize+1)%oceanSize][j] = 2;
                }
                //East empty.
                else if (ocean[i][(j+oceanSize+1)%oceanSize] == 0) {
                    //printf("east empty");
                    ocean[i][(j+oceanSize+1)%oceanSize] = 2;
                }
                    //West empty.
                else if (ocean[i][(j+oceanSize-1)%oceanSize] == 0) {
                    //printf("west empty");
                    ocean[i][(j+oceanSize-1)%oceanSize] = 2;
                }
                    //Northwest empty.
                else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize] == 0) {
                    //printf("northwest empty");
                    ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize-1)%oceanSize] = 2;
                }
                    //Southwest empty.
                else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize] == 0) {
                    //printf("southwest empty");
                    ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize-1)%oceanSize] = 2;
                }
                    //Northeast empty.
                else if (ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize] == 0) {
                    //printf("northeast empty");
                    ocean[(i+oceanSize-1)%oceanSize][(j+oceanSize+1)%oceanSize] = 2;
                }
                    //Southeast empty.
                else if (ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize] == 0) {
                    //printf("southeast empty");
                    ocean[(i+oceanSize+1)%oceanSize][(j+oceanSize+1)%oceanSize] = 2; 
                }
        }
    }
}

//Fish eaten.
void fishEaten(i, j) {

    //If cell is fish.
    if (ocean[i][j]>=1 && ocean[i][j]<=5) {
        //If surrounded by 4 sharks(at least), fish gets eaten.
        if (tSharkC>=4) {
            //printf("\n\nFish is eaten.");
            ocean[i][j] = 0;
        }
    }
    
}

//Species growth.
void growth() {
    x = 0;
    y = 0;
    for(x = 0; x < oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            if (ocean[x][y] != 0) {
                ocean[x][y] = ocean[x][y] + 1;
            }
        }

    }
}

//Species death.
void death() {
    x = 0;
    y = 0;
    for(x = 0; x < oceanSize; x++) {
        for(y = 0; y < oceanSize; y++) {
            if (ocean[x][y] == 5 || ocean[x][y] == 10) {
                ocean[x][y] = 0;
            }
        }

    }
    
}