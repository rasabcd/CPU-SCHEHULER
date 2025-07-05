#include "Scheduler.h"
struct Comparator
{
    bool operator()(pair<Process, int> p1, pair<Process, int> p2)
    {
        return p1.first.priority < p2.first.priority;
    }
};
void MLQ(vector<Process> &Processes, int timequantum, ofstream &outputFile)
{
    int n = Processes.size();
    auto comparator = [](Process p1, Process p2)
    {
        return p1.arrival_time <= p2.arrival_time;
    };
    sort(Processes.begin(), Processes.end(), comparator);

    int ct = 0;
    int curtime = 0;
    vector<pair<int, pair<int, int>>> Timeinfo;
    priority_queue<pair<Process, int>, vector<pair<Process, int>>, Comparator> System_prioritypremitive;
    queue<pair<Process, int>> Interactive_roundrobin;
    queue<pair<Process, int>> Background_FCFS;
    queue<pair<int, int>> track_of_timequantum;
    vector<int> remainingtime(n);

    for (int i = 0; i < n; i++)
    {
        remainingtime[i] = Processes[i].burst_time;
    }
    int index = 0;
    while (ct < n)
    {
        for (int i = index; i < n; i++)
        {
            if (Processes[i].arrival_time <= curtime)
            {
                if (Processes[i].process_type == 's')
                    System_prioritypremitive.push({Processes[i], i});
                if (Processes[i].process_type == 'i')
                    Interactive_roundrobin.push({Processes[i], i});
                if (Processes[i].process_type == 'b')
                    Background_FCFS.push({Processes[i], i});
                index++;
            }
            else
                break;
        }

        if (!System_prioritypremitive.empty())
        {
            if (!track_of_timequantum.empty())
                track_of_timequantum.pop();
            auto Process = System_prioritypremitive.top().first;
            int cur_index = System_prioritypremitive.top().second;
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
                System_prioritypremitive.pop();
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
        else if (!Interactive_roundrobin.empty())
        {
            auto Process = Interactive_roundrobin.front().first;
            int cur_index = Interactive_roundrobin.front().second;
            int start_time = curtime;
            int end_time = start_time + 1;
            int pid = Process.pid;
            curtime = end_time;
            if (!track_of_timequantum.empty())
            {
                int trackpid = track_of_timequantum.front().first;
                if (pid == trackpid)
                {
                    int time = track_of_timequantum.front().second;
                    track_of_timequantum.pop();
                    track_of_timequantum.push({pid, time + 1});
                }
                else
                {
                    track_of_timequantum.pop();
                    track_of_timequantum.push({pid, 1});
                }
            }
            else
            {
                track_of_timequantum.push({pid, 1});
            }
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
                Interactive_roundrobin.pop();
                ct++;
                Processes[cur_index].completion_time = end_time;
                Processes[cur_index].turnaround_time = Processes[cur_index].completion_time - Processes[cur_index].arrival_time;
                Processes[cur_index].waiting_time = Processes[cur_index].turnaround_time - Processes[cur_index].burst_time;
            }
            else
            {
                remainingtime[cur_index] -= 1;
                if (track_of_timequantum.front().second == timequantum)
                {
                    Interactive_roundrobin.pop();
                    Interactive_roundrobin.push({Process, cur_index});
                }
            }
        }
        else if (!Background_FCFS.empty())
        {
            auto Process = Background_FCFS.front().first;
            int cur_index = Background_FCFS.front().second;
            int start_time = curtime;
            int end_time = start_time + 1;
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
                Background_FCFS.pop();
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
        else
        {
            curtime++;
        }
    }
    GanttChart(Timeinfo, outputFile);
    stats(Processes, outputFile);
}