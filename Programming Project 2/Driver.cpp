/*
    to do:
    6. Implement a means to calculate average memory utilization 
        and search time
    7. Implement the ability to free items randomly
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

bool memory_allocate(int * arr, int size, int index, int len);
void memory_free(int * arr, int size, int index);
void memory_print(int * arr, int size);
bool best_fit(int * arr, int size, int len);
bool worst_fit(int * arr, int size, int len);
bool free_specific_index(int * arr, int size, int index);
bool free_specific_index(int * arr, int size, int index);

int main() {
    int response = -1;
    while(response != 1 && response != 2) {
            cout << "For best-fit, enter 1. For worst-fit, enter 2: ";
            cin >> response;
        if(response == 1) {
            cout << "Best-fit selected." << endl;
        } else if (response == 2) {
            cout << "Worst-fit selected." << endl;
        } else {
            cout << "Invalid response! ";
        }
    }
    int memory[64]; //set up the memory
    for(int i = 0; i <= 64; i++) {
        memory[i] = 0;
    }
    memory[0] = -64;

    srand(time(0));//seed random number generation

    int success = 0;
    while(success < 5) {//generate five randomly placed items of random block size between 1 and 8
        if (memory_allocate(memory, 64, rand() % 64, (rand() % 8) + 1)) {
            success++;
        }
    }
    memory_print(memory, 64);

    success = 0;
    bool go = true;
    while(go && success < 50) { //"game loop"
        if(response == 1) {
            if(!best_fit(memory, 64, (rand() % 8) + 1)) {//if allocaiton fails
                go = false;//stop the loop
            }
        }
        if(response == 2) {
            if(!worst_fit(memory, 64, (rand() % 8) + 1)) {//if allocation fails
                go = false;//stop the loop
            }
        }
        
        //figure out how to free random chunks of memory

        success++;
        memory_print(memory, 64);
    }
}

bool memory_allocate(int * arr, int size, int index, int len) {
    int i = index;
    while(i <= index + len) {//check to see if enough space
        if(arr[i] > 0 || i >= size) {
            perror("ERROR: ALLOCATION FAILED.");
            return false;
        }
        i++;
    }

    arr[index] = len;
    i = index + 1;
    while(i < index + len) {//allocate memory
        arr[i] = 1;
        i++;
    }

    memory_free(arr, size, index + len); //update hole afterwards

    i = index;
    while(arr[i] >= 0 && i >= 0) {//update hole before
        i--;
    }
    memory_free(arr, size, i);//should work on an index with negative contents
    return true;
}

void memory_free(int * arr, int size, int index) {
    int i = index + 1;
    int count = 1;
    while(arr[i] <= 1 && i < size) {
        arr[i] = 0;
        i++;
        count++;
    }
    arr[index] = -count;//readjusts hole size
    //printf("overwrote chunk at index %d. (%d blocks)", index, count);
    //cannot call allocate here. Potential for recursion with no base case
    i = index -1;
    count = 0;
    while(i > 0 && arr[i] == 1) {
        arr[i] = 1;
        i--;
        count++;
    }
    arr[i] = count +1;//readjusts size of previous chunk in the case that it is overwritten
}

void memory_print(int * arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool best_fit(int * arr, int size, int len) {
    int best = 64;
    int index_best = -1;
    int i = 0;//current index (starts at beginning)
    while(i < size) {
        if(arr[i] < 0) {//look for starting blocks of the gap
            if(abs(arr[i] + len) < best && abs(arr[i] + len) >= len) {
                best = abs(arr[i] + len);
                index_best = i;
            }
        }
        i += abs(arr[i]);//allows faster advance 
                        //(i.e. value of "-4" would let you move ahead 4 indexes)
    }
    if(index_best != -1) {
        memory_allocate(arr, size, index_best, len); //allocates to the best-fitting index
        return true;
    }
    cout << "ERROR: NO HOLE BIG ENOUGH!" << endl;
    return false;
}

bool worst_fit(int * arr, int size, int len) {
    int worst = len;
    int index_worst = -1;
    int i = 0;//current index (starts at beginning)
    while(i < size) {
        if(arr[i] < 0) {//look for starting blocks of the gap
            if(abs(arr[i] + len) > worst) {//took out    &&abs(arr[i] + len) >= len
                worst = abs(arr[i] - len);
                index_worst = i;
            }
        }
        i += abs(arr[i]);//allows faster advance 
                        //(i.e. value of "-4" would let you move ahead 4 indexes)
    }
    if(index_worst != -1) {
        memory_allocate(arr, size, index_worst, len); //allocates to the best-fitting index
        return true;
    }
    cout << "ERROR: NO HOLE BIG ENOUGH!" << endl;
    return false;
}
