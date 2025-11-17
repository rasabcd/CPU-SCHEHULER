#include "Scheduler.h"
struct Comparator
{
    bool operator()(pair<Process, int> p1, pair<Process, int> p2)
    {
        return p1.first.burst_time > p2.first.burst_time;
    }
};
void SJFNP(vector<Process> &Processes, ofstream &outputFile)
{
    int n = Processes.size();
    auto comparator = [](Process p1, Process p2)
    {
        return p1.arrival_time <= p2.arrival_time;
    };
    sort(Processes.begin(), Processes.end(), comparator);
    priority_queue<pair<Process, int>, vector<pair<Process, int>>, Comparator> pq;
    vector<pair<int, pair<int, int>>> Timeinfo;
    int curtime = 0;
    int ct = 0;
    int index = 0;
    while (ct < n)
    {
        for (int i = index; i < n; i++)
        {
            int arrival_time = Processes[i].arrival_time;
            if (arrival_time <= curtime)
            {
                pq.push({Processes[i], i});
                index++;
            }
            else
                break;
        }
        if (pq.empty())
        {
            curtime = Processes[index].arrival_time;
            continue;
        }
        ct++;
        auto Process = pq.top().first;
        int cur_index = pq.top().second;
        pq.pop();
        int start_time = curtime;
        int end_time = curtime + Process.burst_time;
        curtime = end_time;
        Timeinfo.push_back({Process.pid, {start_time, end_time}});
        Processes[cur_index].completion_time = end_time;
        Processes[cur_index].turnaround_time = Processes[cur_index].completion_time - Processes[cur_index].arrival_time;
        Processes[cur_index].waiting_time = Processes[cur_index].turnaround_time - Processes[cur_index].burst_time;
    }
    GanttChart(Timeinfo, outputFile);
    stats(Processes, outputFile);
}