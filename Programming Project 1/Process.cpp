#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

class Process {
    private:
        unsigned int pid;
        bool is_active;
        unsigned int arriv_time;
        unsigned int tot_cpu_time;
        unsigned int rem_cpu_time;
        unsigned int turnaround;

    public:
        Process(unsigned int pid) {

            this->pid = pid;
            this->is_active = false;
            this->arriv_time = rand() % 22 + 1;
            this->tot_cpu_time = 0;
            this->rem_cpu_time = rand() % 51 + 1;
            this->turnaround = 0;
        }

            // overload the operator> (if required)
        bool operator<(const Process &r) const
        {
            return rem_cpu_time < r.rem_cpu_time;
        }

        unsigned int getPid() {
            return this->pid;
        }

        bool isActive() {
            return this->is_active;
        }

        unsigned int getArrivTime() {
            return this->arriv_time;
        }

        unsigned int getTotCPUTime() {
            return this->tot_cpu_time;
        }

        unsigned int getRemCPUTime() {
            return this->rem_cpu_time;
        }

        //void setPid(unsigned char pid);
        void setActive(bool state){
            this->is_active = state;
        }

        void setArrivTime(unsigned int arriv_time){
            this->arriv_time = arriv_time;
        }

        void incTotCPUTime(){
            this->tot_cpu_time++;
        }

        void decRemCPUTime(){
            this->rem_cpu_time--;
        }

};