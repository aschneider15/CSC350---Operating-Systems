#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <cstdio>

#include "Process.cpp"
using namespace std;

void printTable(vector<Process> v);
Process getSRT(vector<Process> v);
int getTotalRemainingTime(vector<Process> v);

//code begins here  
    int main() {
        
        vector<Process> process_list;
        vector<Process> active_list;


        for(int i = 0; i < 5; i++) {//initialize simulation table
            Process p = Process( i + 1 );
            process_list.emplace_back(p);
        }
        /*
        to do: 
            main loop (until all processes have remaining time of 0)
                check to see if any processes enter the active list
                    if the active list is not empty
                        figure out the process with the srt (not including 0)
                        decrement remaining time of the srt
                            update the srt task in the process list
                            if srt's rt becomes 0, remove it from the active list
                advance time
        */
        int time = 0;
        while(getTotalRemainingTime(process_list) > 0) {//simulation loop
            cout << "time: " << time << endl;
            for(Process & p : process_list) { //check for active processes
                if(p.getArrivTime() == time) {
                    p.setActive(true);
                }
                if(p.isActive()) {
                    active_list.emplace_back(p);//put any arrived tasks on the active list
                }
            }
            if(active_list.size() != 0) {
                //decrement total remaining time of
                for(Process & p : process_list) {
                    if(p.getPid() == getSRT(active_list).getPid() && p.getRemCPUTime() > 0) {
                        p.decRemCPUTime();//decrement rt for srt process
                    }
                }
            }
            for(Process & p : process_list) {
                if(p.getRemCPUTime() > 0 && p.isActive()) {
                    p.incTotCPUTime();//increment total time for all processes
                } else {
                    p.setActive(false);
                    
                }
            }
            active_list.clear();
            printTable(process_list);


            time++;
        }

        
        double att = 0;
        int i = 0;
        for(Process p : process_list) {
            att += p.getTotCPUTime();
            i++;
        }
        att /= i;
        cout << "====================================" << endl << "total average turnaround time: " << att << endl << "====================================" << endl;


        return 0;
    };





void printTable(vector<Process> v) {
    cout << "Process ID:===Is Active===Arrival Time===Turnaround Time===Remaining CPU Time" << endl;
    for(Process p : v) {
        cout << p.getPid() << "               " << p.isActive() << "             " << p.getArrivTime() << "             " 
        << p.getTotCPUTime() << "                " << p.getRemCPUTime() << "             " << endl;
    }
    cout << endl;
}

Process getSRT(vector<Process> v) {
    Process temp = v.at(0);
    for(Process p : v) {
        if(p < temp && p.getRemCPUTime()) {
            temp = p;
        }
    }
    return temp;
}

int getTotalRemainingTime(vector<Process> v) {
    int output = 0;
    for(Process p : v) {
        output += p.getRemCPUTime();
    }
    return output;
}

