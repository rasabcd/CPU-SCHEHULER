#include "Scheduler.h"
void FCFS(vector<Process> &Processes, ofstream &outputFile)
{
    auto comparator = [](Process p1, Process p2)
    {
        return p1.arrival_time <= p2.arrival_time;
    };
    sort(Processes.begin(), Processes.end(), comparator);
    int n = Processes.size();
    int start_time = 0;
    vector<pair<int, pair<int, int>>> Timeinfo;
    for (int i = 0; i < n; i++)
    {
        int arrival_time = Processes[i].arrival_time;
        int burst_time = Processes[i].burst_time;
        start_time = max(start_time, arrival_time);
        Processes[i].completion_time = start_time + burst_time;
        Processes[i].turnaround_time = Processes[i].completion_time - arrival_time;
        Processes[i].waiting_time = Processes[i].turnaround_time - burst_time;
        Timeinfo.push_back({Processes[i].pid, {start_time, start_time + burst_time}});
        start_time += burst_time;
    }
    GanttChart(Timeinfo, outputFile);
    stats(Processes, outputFile);
}