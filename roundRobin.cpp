#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>

using namespace std;

struct Process {
    int pid, AT, BT, remainingBT, CT, TAT, WT;
};

int main() {
    int n, timeQuantum;

    // Input number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Taking input
    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID: ";
        cin >> processes[i].pid;
        cout << "Enter Arrival Time (AT): ";
        cin >> processes[i].AT;
        cout << "Enter Burst Time (BT): ";
        cin >> processes[i].BT;
        processes[i].remainingBT = processes[i].BT;  // Initialize remaining burst time
    }

    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    queue<int> q; // Queue to maintain process execution order
    vector<bool> inQueue(n, false); // Keeps track if a process is in queue
    int currentTime = 0, completed = 0;
    float totalWT = 0;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
        return a.AT < b.AT;
    });

    // Push the first process into the queue
    q.push(0);
    inQueue[0] = true;

    while (completed < n) {
        if (q.empty()) {
            // If no process is available, jump to the next available process
            int nextArrival = 1e9, index = -1;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].remainingBT > 0 && processes[i].AT < nextArrival) {
                    nextArrival = processes[i].AT;
                    index = i;
                }
            }
            currentTime = nextArrival;
            q.push(index);
            inQueue[index] = true;
        }

        int i = q.front();
        q.pop();
        inQueue[i] = false;

        // Execute the process for the time quantum or remaining time
        if (processes[i].remainingBT > timeQuantum) {
            processes[i].remainingBT -= timeQuantum;
            currentTime += timeQuantum;
        } else {
            currentTime += processes[i].remainingBT;
            processes[i].CT = currentTime; // Completion Time
            processes[i].remainingBT = 0;
            completed++;
        }

        // Add new arrivals to the queue
        for (int j = 0; j < n; j++) {
            if (processes[j].AT <= currentTime && processes[j].remainingBT > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // If the process still has burst time left, re-add it to the queue
        if (processes[i].remainingBT > 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    // Calculate TAT and WT
    for (int i = 0; i < n; i++) {
        processes[i].TAT = processes[i].CT - processes[i].AT; // Turnaround Time
        processes[i].WT = processes[i].TAT - processes[i].BT; // Waiting Time
        totalWT += processes[i].WT;
    }

    // Display results in a table
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" 
             << processes[i].AT << "\t" 
             << processes[i].BT << "\t" 
             << processes[i].CT << "\t" 
             << processes[i].TAT << "\t" 
             << processes[i].WT << endl;
    }

    // Calculate and display Average Waiting Time
    float avgWT = totalWT / n;
    cout << "\nAverage Waiting Time: " << avgWT << " ms" << endl;

    return 0;
}
