#include "Scheduler.h"
struct Comparator
{
    bool operator()(pair<Process, int> p1, pair<Process, int> p2)
    {
        return p1.first.burst_time > p2.first.burst_time;
    }
};
void SJFP(vector<Process> &Processes, ofstream &outputFile)
{
    int n = Processes.size();
    auto comparator = [](Process p1, Process p2)
    {
        return p1.arrival_time <= p2.arrival_time;
    };
    sort(Processes.begin(), Processes.end(), comparator);
    priority_queue<pair<Process, int>, vector<pair<Process, int>>, Comparator> pq;
    vector<int> remainingtime(n);
    for (int i = 0; i < n; i++)
    {
        remainingtime[i] = Processes[i].burst_time;
    }
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
                index = i + 1;
            }
            else
                break;
        }
        if (pq.empty())
        {
            curtime++;
            continue;
        }
        auto Process = pq.top().first;
        int cur_index = pq.top().second;
        int start_time = curtime;
        int end_time = curtime + 1;
        int pid = Process.pid;
        curtime = end_time;
        if (Timeinfo.size() >= 1)
        {
            int size = Timeinfo.size();
            int lastpid = Timeinfo[size - 1].first;
            if (pid == lastpid)
            {
                int new_start_time = Timeinfo[size - 1].second.first;
                int new_end_time = end_time;
                Timeinfo.pop_back();
                Timeinfo.push_back({pid, {new_start_time, new_end_time}});
            }
            else
            {
                Timeinfo.push_back({pid, {start_time, end_time}});
            }
        }
        else
        {
            Timeinfo.push_back({pid, {start_time, end_time}});
        }
        if (remainingtime[cur_index] == 1)
        {
            pq.pop();
            ct++;
            Processes[cur_index].completion_time = end_time;
            Processes[cur_index].turnaround_time = Processes[cur_index].completion_time - Processes[cur_index].arrival_time;
            Processes[cur_index].waiting_time = Processes[cur_index].turnaround_time - Processes[cur_index].burst_time;
        }
        else
        {
            remainingtime[cur_index] -= 1;
        }
    }
    GanttChart(Timeinfo, outputFile);
    stats(Processes, outputFile);
}
