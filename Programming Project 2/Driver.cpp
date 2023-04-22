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
int free_blocks(int * arr, int size, int lastfree);
double get_memory_occupancy(int * arr, int size);

int main() {
    
    int memory[64]; //set up the memory
    for(int i = 0; i <= 64; i++) {
        memory[i] = 0;
    }
    memory[0] = -64;

    srand(time(0));//seed random number generation

    int success = 0;
    while(success < 5) {//generate five randomly placed items of random block size between 1 and 8
        if (memory_allocate(memory, 64, rand() % 64, (rand() % 7) + 2)) {
            success++;
        }
    }

    success = 0;
    bool go = true;
    int lastfree = -1;//indicates last block of memory "randomly freed"
    double avg = 0.0;

    int response = -1;
    while(response != 1 && response != 2) {
            cout << "For best-fit, enter 1. For worst-fit, enter 2: ";
            cin >> response;
            memory_print(memory, 64);
        if(response == 1) {
            cout << "Best-fit selected." << endl;

            while(go && success < 50) { //"game loop"
                lastfree = free_blocks(memory, 64, lastfree);
                go = best_fit(memory, 64, (rand() % 7) + 2);
                success++;
                memory_print(memory, 64);
                avg += get_memory_occupancy(memory, 64);
            }
            break;
        } else if (response == 2) {
            cout << "Worst-fit selected." << endl;

            while(go && success < 50) { //"game loop"
                lastfree = free_blocks(memory, 64, lastfree);
                go = worst_fit(memory, 64, (rand() % 7) + 2);
                success++;
                memory_print(memory, 64);
                avg += get_memory_occupancy(memory, 64);
            }
            break;
        } else {
            cout << "Invalid response! ";
        }
    }
    cout << "================================================================" << endl;
    cout << "================================================================" << endl;
    cout << "Average memory utilization: " << (avg /= 50) << endl;
    cout << "================================================================" << endl;
    cout << "================================================================" << endl;
}

bool memory_allocate(int * arr, int size, int index, int len) {
    int i = index;
    while(i < index + len) {//check to see if enough space
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
}

void memory_print(int * arr, int size) {
    char output[2*size];
    for(int i = 0; i < size; i++) {
            if(arr[i] > 1) {
                output[i] = '#';
            } else if(arr[i] == 1) {
                output[i] = '*';
            } else {
                output[i] = '_';
            }
            //output[2*i + 1] = ' ';
    }
    cout << output << endl;
    cout << "================================================================" << endl;
}

bool best_fit(int * arr, int size, int len) {
    int best = 64;
    int index_best = -1;
    int i = 0;//current index (starts at beginning)
    while(i < size) {
        if(arr[i] < 0) {//look for starting blocks of the gap
            if((-arr[i] < best) && (-arr[i] >= len)) {
                best = abs(arr[i]);
                index_best = i;
            }
        }
        i += abs(arr[i]);//allows faster advance 
                        //(i.e. value of "-4" would let you move ahead 4 indexes)
    }
    if(index_best == -1) {
        cout << "ERROR: NO HOLE BIG ENOUGH! SIZE NEEDED: " << len << endl;
        return false;
    }
    //cout << "Allocated segment of size " << len << " at index " << index_best << endl;
    memory_allocate(arr, size, index_best, len); //allocates to the best-fitting index
    return true;
}

bool worst_fit(int * arr, int size, int len) {
    int worst = len;
    int index_worst = -1;
    int i = 0;//current index (starts at beginning)
    while(i < size) {
        if(arr[i] < 0) {//look for starting blocks of the gap
            if((-arr[i] >= worst)) {//took out    &&abs(arr[i] + len) >= len
                worst = -arr[i];
                index_worst = i;
            }
        }
        i++;
        //i += abs(arr[i]);//allows faster advance 
                        //(i.e. value of "-4" would let you move ahead 4 indexes)
    }
    if(index_worst == -1) {
        cout << "ERROR: NO HOLE BIG ENOUGH! SIZE NEEDED: " << len << endl;
        return false;
    }
    //cout << "Allocated segment of size " << len << " at index " << index_worst << endl;
    memory_allocate(arr, size, index_worst, len); //allocates to the best-fitting index
    return true;
}

int free_blocks(int * arr, int size, int lastfree) {
    int i = lastfree;
    while(arr[i] <= 1) {
        i = (i+1) % size; //loops back to index 0
    }
    memory_free(arr, size, i);
    return i;
}

double get_memory_occupancy(int * arr, int size) {
    double result;
    for(int i = 0; i < size; i++) {
        if(arr[i] > 0) {
            result++;
        }
    }
    result /= size;
    return result;
}