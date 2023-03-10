#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "SimulationTable.hpp"

SimTable::SimTable(){
    this->timetable = 0;

    srand(time(NULL));//seed the random number generator
    //instantiate processes
    unsigned char count = 0;
    for(Process p : this->processList) {
        p.process_id = count;
        //is_active will be set to 1 upon arrival
        p.arrival_time = rand() % 200;
        //departure_time will be determined when process deactivates
        p.cpu_time_total = rand() % 50;
        p.cpu_time_remaining = p.cpu_time_total;
        //turnaround_time will be determined when process deactivates
        count++;
    }
};

unsigned int SimTable::getCurrentTime() {
    return this->timetable;
};

void SimTable::advance() {
    this->timetable++;
};

unsigned int SimTable::getAvgTurnaroundTime() {
    unsigned int sum = 0;
    unsigned char count = 0;
    for(Process p : processList) {
        if(p.is_active) {//handle if not all processes are done
            perror("ERROR: not all processes have finished.");
            break;
        }
        sum += p.turnaround_time;
        count++;
    }
    sum /= count;
    return sum;
};

unsigned int SimTable::getAvgTotalCPUTime() {
    unsigned int sum = 0;
    unsigned char count = 0;
    for(Process p : processList) {
        if(p.is_active) {//handle if not all processes are done
            perror("ERROR: not all processes have finished.");
            break;
        }
        sum += p.cpu_time_total;
        count++;
    }
    sum /= count;
    return sum;
};

unsigned char SimTable::getTotalRemainingTime() {
    unsigned char sum = 0;
    for(Process p : processList) {
        sum += p.cpu_time_remaining;
    }
    return sum;
};