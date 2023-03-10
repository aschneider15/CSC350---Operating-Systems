#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SimulationTable.cpp"

using namespace std;

int main(){
    SimTable st;
    while(st.getTotalRemainingTime > 0) {//simulation loop
        /*
        see if any processes are ready to run
        if there is a process ready, activate it
            set is_active to true
            set arrival time to current time
        If there are multiple active processes, figure out who gets to run
        */    
       cout << "hello world" << endl;
    }
    cout << "hello world" << endl;
    return 0;
}

/* repeat until all processes have terminated */
/* if no process is ready to run, just advance t */
/* Ex: FIFO, SJF, SRT */
/* pᵢ has accumulated 1 CPU time unit */
/* process i has terminated */
/* process i is excluded from further consideration */
/* the turnaround time of process i is the time since arrival, TTᵢ, until the current time t */