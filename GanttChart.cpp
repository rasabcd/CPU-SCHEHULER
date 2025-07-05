#include "Scheduler.h"
void GanttChart(vector<pair<int, pair<int, int>>> Timeinfo, ofstream &outputFile)
{

    outputFile << std::setw(50) << right << "Gantt Chart" << std::endl
               << std::endl;
    int start = 0;
    for (auto Process : Timeinfo)
    {
        if (Process.second.first != start)
        {
            outputFile << "|   " << "  ";
            start = Process.second.first;
        }
        outputFile << "|  P" << Process.first << "  ";
        start = Process.second.second;
    }
    outputFile << "|";
    start = 0;
    outputFile << std::endl;
    for (auto Process : Timeinfo)
    {

        if (Process.second.first != start)
        {
            outputFile << setw(6) << left << start;
            start = Process.second.first;
        }
        outputFile << setw(7) << left << Process.second.first;
        start = Process.second.second;
    }
    outputFile << setw(6) << left << start;
    outputFile << std::endl;
    outputFile << std::endl;
    outputFile << std::endl;
    outputFile << std::endl;
    outputFile << std::endl;
}