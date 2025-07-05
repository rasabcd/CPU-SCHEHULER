#include "Scheduler.h"
void stats(vector<Process> &Processes, ofstream &outputFile)
{
    outputFile << std::setw(50) << right << "Statistics" << std::endl
               << std::endl;
    outputFile << std::setw(20) << std::left << "Process";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.pid;
    }
    outputFile << std::endl;
    int n = Processes.size();
    for (int i = 0; i < 20 + 10 * (n); i++)
    {
        outputFile << "-";
    }
    outputFile << std::endl;
    outputFile << std::setw(20) << std::left << "Arrival time";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.arrival_time;
    }
    outputFile << std::endl;
    outputFile << std::setw(20) << std::left << "Burst time";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.burst_time;
    }
    outputFile << std::endl;
     outputFile << std::setw(20) << std::left << "Priority";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.priority;
    }
    outputFile << std::endl;
    
    outputFile << std::setw(20) << std::left << "Completion time";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.completion_time;
    }
    outputFile << std::endl;
    outputFile << std::setw(20) << std::left << "turnaround time";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.turnaround_time;
    }
    outputFile << std::endl;
    outputFile << std::setw(20) << std::left << "Waiting time";
    for (auto Process : Processes)
    {
        outputFile << std::setw(10) << std::left << Process.waiting_time;
    }
    outputFile << std::endl;
    outputFile << std::endl;
    float averageWating_time = 0;
    for (auto Process : Processes)
    {
        averageWating_time += Process.waiting_time;
    }
    averageWating_time = averageWating_time / n;
    outputFile << std::setw(23) << std::left << "Average Waiting time = " << averageWating_time;
}