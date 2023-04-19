/*
    to do:
    1. Implement measures to correct allocated block size for memory residents
    2. Implement allocation based on best-fit
    3. Implement allocation based on worst-fit
    4. Randomize block sizes and indexes
    5. Implement "game loop"
    6. Implement a means to calculate average memory utilization 
        and search time
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

int main() {
    int memory[64];
    
    for(int i = 0; i <= 64; i++) {
        memory[i] = 0;
    }
    memory[0] = -64;

    memory_allocate(memory, 64, 0, 7);
    memory_print(memory, 64);

    memory_allocate(memory, 64, 7, 4);
    memory_print(memory, 64);

    memory_free(memory, 64, 5);
    memory_print(memory, 64);
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
}

void memory_print(int * arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
