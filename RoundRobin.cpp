#include "Scheduler.h"
void RR(vector<Process> &Processes, int timequantum, ofstream &outputFile)
{
    int n = Processes.size();
    auto comparator = [](Process p1, Process p2)
    {
        return p1.arrival_time <= p2.arrival_time;
    };
    sort(Processes.begin(), Processes.end(), comparator);
    queue<pair<Process, int>> q;
    int ind = 0;
    for (auto Process : Processes)
    {
        q.push({Process, ind});
        ind++;
    }
    int curtime = 0;
    vector<pair<int, pair<int, int>>> Timeinfo;
    while (!q.empty())
    {
        auto Process = q.front().first;
        int index = q.front().second;
        q.pop();
        int arrival_time = Process.arrival_time;
        int burst_time = Process.burst_time;
        int start_time = max(curtime, arrival_time);
        int time = min(timequantum, burst_time);
        int end_time = start_time + time;
        curtime = end_time;
        if (q.empty())
        {
            Processes[index].completion_time = start_time + burst_time;
            Processes[index].turnaround_time = Processes[index].completion_time - arrival_time;
            Processes[index].waiting_time = Processes[index].turnaround_time - burst_time;
            Timeinfo.push_back({Processes[index].pid, {start_time, start_time + burst_time}});
            break;
        }
        Timeinfo.push_back({Processes[index].pid, {start_time, end_time}});
        if (time != burst_time)
        {
            Process.burst_time -= time;
            q.push({Process, index});
        }
        else
        {
            Processes[index].completion_time = curtime;
            Processes[index].turnaround_time = Processes[index].completion_time - arrival_time;
            Processes[index].waiting_time = Processes[index].turnaround_time - burst_time;
        }
    }
    GanttChart(Timeinfo, outputFile);
    stats(Processes, outputFile);
}
