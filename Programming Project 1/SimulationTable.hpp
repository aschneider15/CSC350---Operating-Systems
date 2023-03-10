class SimTable {
    private:
        struct Process {
            char process_id;
            bool is_active;
            unsigned int arrival_time;
            unsigned int departure_time;
            unsigned int cpu_time_total;
            unsigned int cpu_time_remaining;
            unsigned int turnaround_time; //departure time-arrival time
        };
        
        Process processList[5];
        Process activeList[5];
        unsigned int timetable;

    public:
        SimTable();
        unsigned int getCurrentTime();
        void advance();
        unsigned int getAvgTurnaroundTime();
        unsigned int getAvgTotalCPUTime();
        unsigned char getTotalRemainingTime();

};