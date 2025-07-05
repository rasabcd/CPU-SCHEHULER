#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_h
#include <bits/stdc++.h>
using namespace std;
class Process
{
public:
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    char process_type;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    Process()
    {
    }
};

void GanttChart(vector<pair<int, pair<int, int>>> Timeinfo, ofstream &outputFile);
void stats(vector<Process> &Processes, ofstream &outputFile);

void FCFS(vector<Process> &Processes, ofstream &outputFile);
void SJFNP(vector<Process> &Processes, ofstream &outputFile);
void SJFP(vector<Process> &Processes, ofstream &outputFile);
void RR(vector<Process> &Processes, int timequantum, ofstream &outputFile);
void Priority_NP(vector<Process> &Processes, ofstream &outputFile);
void Priority_P(vector<Process> &Processes, ofstream &outputFile);
void MLQ(vector<Process> &Processes, int timequantum,ofstream &outputFile);

#endif