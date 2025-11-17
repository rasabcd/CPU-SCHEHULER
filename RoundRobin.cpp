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
    vector<pair<int, pair<int, int>>> Timeinfo;
    vector<int> actual_burstTime(n);
    for (int i = 0; i < n; i++)
    {
        actual_burstTime[i] = Processes[i].burst_time;
    }
    int index = 0;
    int ct = 0;
    int curtime = 0;
    while (ct < n)
    {
        for (int i = index; i < n; i++)
        {
            int arrival_time = Processes[i].arrival_time;
            if (arrival_time <= curtime)
            {
                q.push({Processes[i], i});
                index = i + 1;
            }
            else
                break;
        }
        if (q.empty())
        {
            curtime = Processes[index].arrival_time;
            continue;
        }
        auto Process = q.front().first;
        int cur_index = q.front().second;
        int start_time = curtime;
        int end_time = curtime + min(timequantum, Processes[cur_index].burst_time);
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
        if (Processes[cur_index].burst_time == min(timequantum, Processes[cur_index].burst_time))
        {
            q.pop();
            ct++;
            Processes[cur_index].completion_time = end_time;
            Processes[cur_index].turnaround_time = Processes[cur_index].completion_time - Processes[cur_index].arrival_time;
            Processes[cur_index].waiting_time = Processes[cur_index].turnaround_time - actual_burstTime[cur_index];
        }
        else
        {
            q.pop();
            Processes[cur_index].burst_time -= timequantum;
            for (int i = index; i < n; i++)
            {
                int arrival_time = Processes[i].arrival_time;
                if (arrival_time <= curtime)
                {
                    q.push({Processes[i], i});
                    index = i + 1;
                }
                else
                    break;
            }
            q.push({Processes[cur_index], cur_index});
        }
    }

    for (int i = 0; i < n; i++)
    {
        Processes[i].burst_time = actual_burstTime[i];
    }

    GanttChart(Timeinfo, outputFile);
    stats(Processes, outputFile);
}
