#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "SimulationTable.hpp"

SimTable::SimTable(){
    this->timetable = 0;

    srand(time(NULL));//seed the random number generator
    //instantiate processes
    unsigned char count = 1;
    for(Process p : this->processList) {
        p.process_id = count;
        //is_active will be set to 1 upon arrival
        p.is_active = false;
        p.arrival_time = rand() % 20;
        //departure_time will be determined when process deactivates
        p.cpu_time_total = rand() % 5;
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

void SimTable::processesReady() {
    Process ready[5] = {};
    unsigned char i = 0;
    for(Process p : processList) {
        if (p.arrival_time == this->timetable) {
            p.is_active = true;
            ready[i] = p;
            i++;
        }
    }
    for(int i = 0; i < 5; i++) {
        this->activeList[i] = ready[i];
    }
};

/*
SimTable::Process SimTable::calculateSRT() {
    Process shortest = this->activeList[0];
    for(Process p : this->activeList) {
        if((p.cpu_time_remaining < shortest.cpu_time_remaining) && (shortest.cpu_time_remaining != 0)) {
            shortest = p;
        } else if(p.cpu_time_remaining == 0) {
            removeProcessFromActiveList(p);
        }
    }
    return shortest;
};

void SimTable::runProcess() {
    this->setRunningProcess( calculateSRT() );
    this->runningProcess.cpu_time_remaining--;

}
void SimTable::setRunningProcess(Process  p){
    this->runningProcess = p;
}
*/
void SimTable::removeProcessFromActiveList(Process &p){//this one's suspect. Don't trust on compile...
    for(int i = 0; i < 5; i++) {
        if(&(this->activeList[i]) == &p) {
            for(int j = i; j < 5; j++) {
                activeList[j+1] = activeList[j];
            }
        }
    }
}

void SimTable::display() {
    std::cout << "========================================================================" << std::endl;
    for(Process p : processList) {
        std::cout << "process ID: " << p.process_id << ": " << "active: " << p.is_active << " | arrival time: " << p.arrival_time << " | total CPU time: " << p.cpu_time_total
             << " | remaining CPU time: " << p.cpu_time_remaining << " | turnaround time: " << p.turnaround_time << std::endl;
    }
}

