#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int id, arrival, burst, priority, ct, tat, wt, remaining, start;
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

/// First Come First Serve Scheduling Algorithm
void fcfs()
{
    vector<Process> process = inputProcesses("fcfs");
    sort(process.begin(), process.end(), [](Process a, Process b)
         { return a.arrival < b.arrival; });

    int time = 0;

    for (auto &p : process)
    {
        int start = time;
        time = max(time, p.arrival);
        p.start = time;
        p.ct = time + p.burst;
        time += p.burst;
    }

    CalculateTime(process);
}

// Shortest Job First Scheduling Algorithm
void sjf()
{   
    vector<Process> process = inputProcesses("sjf");
    int complete = 0;
    int n = process.size();

    vector<bool> isCompleted(n, false);
    int time = 0;

    while (complete < n)
    {
        int minPro = INT_MAX;
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && time >= process[i].arrival && minPro > process[i].burst)
            {
                minPro = process[i].burst;
                index = i;
            }
        }

        if (index == -1)
        {
            time++;
        }
        else
        {
            process[index].start = time;
            process[index].ct = time + process[index].burst;
            time = process[index].ct;
            isCompleted[index] = true;
            complete++;
        }
    }
    CalculateTime(process);
}

// Shortest Remaining Time First Scheduling Algorithm
void srtf()
{
    vector<Process> process = inputProcesses("srtf");
    int complete = 0;
    int n = process.size();
    int time = 0;

    while (complete < n)
    {
        int minPro = INT_MAX;
        int index = -1;
        for (int i = 0; i < n; i++)
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

void priority()
{
    vector<Process> process = inputProcesses("priority");
    int time = 0;
    int complete = 0;
    int n = process.size();
    vector<int> completed(n, 0);
    while (complete < n)
    {
        int highpriority = INT_MAX;
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && time >= process[i].arrival && process[i].priority < highpriority)
            {
                highpriority = process[i].priority;
                index = i;
            }
        }

        if (index == -1)
        {
            time++;
        }
        else
        {
            process[index].start = time;
            process[index].ct = process[index].start + process[index].burst;
            complete++;
            completed[index] = 1;
            time = process[index].ct;
        }
    }
    CalculateTime(process);
}

// Preemptive Priority
void preemptive_priority()
{
    vector<Process> process = inputProcesses("priority");
    int complete = 0;
    int time = 0;
    int n = process.size();
    while (complete < n)
    {
        int high = INT_MAX;
        int index = 0;
        for (int i = 0; i < n; i++)
        {
            if (process[i].arrival <= time && process[i].remaining > 0 && process[i].priority < high)
            {
                high = process[i].priority;
                index = i;
            }
        }

        time++;
        if (index != -1)
        {
            process[index].remaining--;

            if (process[index].remaining == 0)
            {
                process[index].ct = time;
                complete++;
            }
        }
    }
    CalculateTime(process);
}

// Round Robin

void roundrobin()
{
    vector<Process> process = inputProcesses("roundrobin");
    int quant;
    cout << "Enter the value of quantum number:" << endl;
    cin >> quant;

    int n = process.size();
    int complete = 0;
    int time = 0;

    queue<int> q;
    vector<bool> visited(n, false);

    sort(process.begin(), process.end(), [](Process a, Process b)
         { return a.arrival < b.arrival; });

    for (int i = 0; i < n; i++)
    {
        if (process[i].arrival == time)
        {
            q.push(i);
            visited[i] = true;
        }
    }

    while (q.size() || complete < n)
    {
        if (!q.size())
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && process[i].arrival <= time)
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
            continue;
        }

        int index = q.front();
        q.pop();

        int exe = min(quant, process[index].remaining);
        process[index].remaining -= exe;

        time += exe;

        if (process[index].remaining == 0)
        {
            process[index].ct = time;
            complete++;
        }

        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && process[j].arrival <= time)
            {
                q.push(j);
                visited[j] = true;
            }
        }
        if (process[index].remaining > 0)
        {
            q.push(index);
        }
    }
    CalculateTime(process);
}

int main()
{
    int choice;
    while (true)
    {
        cout << "1.FCFS\n2.SJF\n3.SRTF\n4.Non Preemtive Priority\n5.Preemtive Priority\n6.Round Robin\n7.Exit\nEnter your choice: ";
        cin >> choice;
        if (choice == 7)
            break;
        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            srtf();
            break;
        case 4:
            priority();
            break;
        case 5:
            preemptive_priority();
            break;
        case 6:
            roundrobin();
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}