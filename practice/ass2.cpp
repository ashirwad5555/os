#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct Process
{
    int id,
        tat,
        arrival,
        burst,
        priority,
        wt,
        start,
        ct,
        remaining;
};

void CalculateTime(vector<Process> &p)
{
    int totalwt = 0;
    int totaltat = 0;
    cout << "\n+-----+------------+----------+------------+--------------+----------+\n";
    cout << "| PID | Arrival    | Burst    | Completion | Turnaround   | Waiting  |\n";
    cout << "+-----+------------+----------+------------+--------------+----------+\n";
    for (auto &i : p)
    {
        i.tat = i.ct - i.arrival;
        i.wt = i.tat - i.burst;
        totalwt += i.wt;
        totaltat += i.tat;
    }
    for (auto &i : p)
    {
        cout << "| " << i.id << "  |" << i.arrival << "         | " << i.burst << "      | " << i.ct << "        | " << i.tat << "          | " << i.wt << "      |\n";
        cout << "+-----+------------+----------+------------+--------------+----------+\n";
    }
    cout << "Average Waiting Time: " << (float)totalwt / p.size() << endl;
    cout << "Average Turnaround Time: " << (float)totaltat / p.size() << endl;
    cout << "Total Waiting Time: " << totalwt << endl;
}

vector<Process> inputProcesses(string algo)
{
    int n;
    cout << "Enter the number of the processes:" << endl;
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        cout << "Enter the value of Arrival and Burst Time of having Process id" << p[i].id << endl;
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }

    if (algo == "priority")
    {
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the value of Priority of having Process id" << (p[i].id) << endl;
            cin >> p[i].priority;
        }
    }
    return p;
}

void displayGantt(vector<int> chart)
{
    int n = chart.size();

    for (int i = 0; i < n; i++)
    {
        if (chart[i] == -1)
            cout << "| Idle ";
        else
            cout << "| p" << chart[i] << " ";
    }

    cout << "|\n0";

    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << (i + 1);
    }
}

void fcfs()
{
    vector<Process> processes = inputProcesses("fcfs");
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.arrival < b.arrival; });
    int time = 0;
    for (auto &p : processes)
    {
        int start = time;
        time = max(p.arrival, time);
        p.start = time;
        p.ct = time + p.burst;
        time += p.burst; // cpu time
    }

    CalculateTime(processes);
}

void sjf()
{
    vector<Process> processes = inputProcesses("sjf");
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.arrival < b.arrival; });

    int count = 0;
    int n = processes.size();
    int time = 0;

    vector<bool> completed(n, false);

    while (count < n)
    {
        int minPro = INT_MAX;
        int index = -1;
        for (int i = 0; i < processes.size(); i++)
        {
            if (!completed[i] && processes[i].arrival <= time && processes[i].burst < minPro)
            {
                minPro = processes[i].burst;
                index = i;
            }
        }

        if (index == -1)
        {
            time++;
        }
        else
        {
            // execute the sjf
            processes[index].start = max(time, processes[index].arrival);
            processes[index].ct = time + processes[index].burst;
            time = processes[index].ct;
            completed[index] = true;
            count++;
        }
    }

    CalculateTime(processes);
}

void srjf()
{
    vector<Process> process = inputProcesses("srtf");
    int complete = 0;
    int n = process.size();
    int time = 0;

    while (complete < n)
    {
        int minPro = INT_MAX;
        int index = -1;
        for (int i = 0; i < process.size(); i++)
        {
            if (process[i].arrival <= time && process[i].remaining > 0 && process[i].remaining < minPro)
            {
                minPro = process[i].remaining;
                index = i;
            }
        }
        time++;

        if (index != -1)
        {
            process[index].remaining--;
            if (process[index].remaining == 0)
            {
                complete++;
                process[index].ct = time;
            }
        }
    }

    CalculateTime(process);
}

void rr()
{
    int quant;
    cout << "Enter the quant" << endl;
    cin >> quant;

    vector<Process> processes = inputProcesses("roundrobin");
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.arrival < b.arrival; });

    int completed = 0;
    int n = processes.size();
    int time = 0;

    queue<int> q;
    vector<bool> visited(n, false);

    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i].arrival == time)
        {
            q.push(i);
            visited[i] = true;
        }
    }

    while (q.size() || completed < n)
    {
        if (!q.size())
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && processes[i].arrival <= time)
                {
                    q.push(i);
                    visited[i] = true;
                }
            }

            continue;
        }

        int index = q.front();
        q.pop();

        int exe = min(processes[index].remaining, quant);
        processes[index].remaining -= exe;
        time += exe;

        if (processes[index].remaining == 0)
        {
            processes[index].ct = time;
            completed++;
        }

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && processes[i].arrival <= time)
            {
                q.push(i);
                visited[i] = true;
            }
        }

        if (processes[index].remaining > 0)
        {
            q.push(index);
        }
    }

    CalculateTime(processes);
}

int main()
{
    // fcfs();
    // sjf();
    // srjf();
    rr();
}