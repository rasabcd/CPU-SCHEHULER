
#include <bits/stdc++.h>
#include "Scheduler.h"
using namespace std;
int main()
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    if (inputFile.is_open() && outputFile.is_open())
    {
        int type;
        inputFile >> type;
        int n;
        inputFile >> n;
        vector<Process> Processes;
        for (int i = 0; i < n; i++)
        {
            Process p = Process();
            inputFile >> p.pid >> p.arrival_time >> p.burst_time >> p.priority >> p.process_type;
            Processes.push_back(p);
        }
        if (type == 1)
        {
            FCFS(Processes, outputFile);
        }
        if (type == 2)
        {
            SJFNP(Processes, outputFile);
        }
        if (type == 3)
        {
            SJFP(Processes, outputFile);
        }
        if (type == 4)
        {
            RR(Processes, 2, outputFile);
        }
        if (type == 5)
        {
            Priority_NP(Processes, outputFile);
        }
        if (type == 6)
        {
            Priority_P(Processes, outputFile);
        }
        if (type == 7)
        {
            MLQ(Processes, 2, outputFile);
        }

        inputFile.close();
        outputFile.close();
    }
    else
    {
        cerr << "error in opening input or output file" << std::endl;
        return 1;
    }
    return 0;
}