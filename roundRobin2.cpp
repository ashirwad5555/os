#include <iostream>
#include <queue>
#include <iomanip>
#include<algorithm>

using namespace std;

struct Process {
    int id, arrival, burst, remaining, completion, turnaround, waiting;
};

// Function to calculate Turnaround Time and Waiting Time
void calculateTimes(Process processes[], int n, int timeQuantum) {
    queue<int> q;
    int time = 0, completed = 0;
    bool inQueue[n] = {false};

    // Sort by Arrival Time
    sort(processes, processes + n, [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    q.push(0);
    inQueue[0] = true;

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (processes[i].remaining > timeQuantum) {
            time += timeQuantum;
            processes[i].remaining -= timeQuantum;
        } else {
            time += processes[i].remaining;
            processes[i].remaining = 0;
            processes[i].completion = time;
            processes[i].turnaround = processes[i].completion - processes[i].arrival;
            processes[i].waiting = processes[i].turnaround - processes[i].burst;
            completed++;
        }

        // Add new processes to the queue
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival <= time && processes[j].remaining > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // Requeue the current process if not completed
        if (processes[i].remaining > 0) {
            q.push(i);
        }
    }

    // Calculate Average TAT and WT
    double avgTAT = 0, avgWT = 0;
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        avgTAT += processes[i].turnaround;
        avgWT += processes[i].waiting;
        cout << processes[i].id << "\t" << processes[i].arrival << "\t"
             << processes[i].burst << "\t" << processes[i].completion << "\t"
             << processes[i].turnaround << "\t" << processes[i].waiting << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;
}

int main() {
    int n, timeQuantum;

    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];

    cout << "Enter Process ID, Arrival Time, Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].id >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;  // Initialize remaining time
    }

    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    calculateTimes(processes, n, timeQuantum);

    return 0;
}
