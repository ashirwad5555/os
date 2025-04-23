#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <climits>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int remaining_time;
};

void calculateWaitingTimeFCFS(std::vector<Process>& processes) {
    processes[0].waiting_time = 0;
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].waiting_time = processes[i - 1].completion_time - processes[i].arrival_time;
        if (processes[i].waiting_time < 0) {
            processes[i].waiting_time = 0;
        }
        processes[i].completion_time = processes[i].arrival_time + processes[i].waiting_time + processes[i].burst_time;
    }
}

void calculateTurnaroundTime(std::vector<Process>& processes) {
    for (auto& process : processes) {
        process.turnaround_time = process.waiting_time + process.burst_time;
    }
}

void calculateAvgTimes(const std::vector<Process>& processes) {
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.waiting_time;
        total_turnaround_time += process.turnaround_time;
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << total_turnaround_time / processes.size() << "\n";
}

void printTable(const std::vector<Process>& processes) {
    std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& process : processes) {
        std::cout << process.pid << "\t" << process.arrival_time << "\t" << process.burst_time << "\t" 
                  << process.completion_time << "\t" << process.turnaround_time << "\t" << process.waiting_time << "\n";
    }
}

void FCFS(std::vector<Process> processes) {
    calculateWaitingTimeFCFS(processes);
    calculateTurnaroundTime(processes);

    std::cout << "FCFS Scheduling\n";
    printTable(processes);
    calculateAvgTimes(processes);
}

bool compareBurstTime(Process a, Process b) {
    return a.burst_time < b.burst_time;
}

void SJFNonPreemptive(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), compareBurstTime);
    calculateWaitingTimeFCFS(processes);
    calculateTurnaroundTime(processes);

    std::cout << "SJF Non-Preemptive Scheduling\n";
    printTable(processes);
    calculateAvgTimes(processes);
}

void SJFPreemptive(std::vector<Process> processes) {
    int n = processes.size();
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    for (auto& process : processes) {
        process.remaining_time = process.burst_time;
    }

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((processes[j].arrival_time <= t) && 
                (processes[j].remaining_time < minm) && 
                (processes[j].remaining_time > 0)) {
                minm = processes[j].remaining_time;
                shortest = j;
                check = true;
            }
        }

        if (!check) {
            t++;
            continue;
        }

        processes[shortest].remaining_time--;
        minm = processes[shortest].remaining_time;
        if (minm == 0) minm = INT_MAX;

        if (processes[shortest].remaining_time == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            processes[shortest].completion_time = finish_time;
            processes[shortest].waiting_time = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            if (processes[shortest].waiting_time < 0) processes[shortest].waiting_time = 0;
        }
        t++;
    }

    for (auto& process : processes) {
        process.turnaround_time = process.burst_time + process.waiting_time;
    }

    std::cout << "SJF Preemptive Scheduling\n";
    printTable(processes);
    calculateAvgTimes(processes);
}

void RoundRobin(std::vector<Process> processes, int quantum) {
    std::queue<Process> q;
    for (const auto& process : processes) {
        q.push(process);
    }

    int time = 0;
    std::vector<Process> result;

    while (!q.empty()) {
        Process current = q.front();
        q.pop();
        if (current.burst_time > quantum) {
            time += quantum;
            current.burst_time -= quantum;
            q.push(current);
        } else {
            time += current.burst_time;
            current.waiting_time = time - current.burst_time - current.arrival_time;
            if (current.waiting_time < 0) current.waiting_time = 0;
            current.turnaround_time = time - current.arrival_time;
            current.completion_time = time;
            result.push_back(current);
        }
    }

    std::cout << "Round Robin Scheduling\n";
    printTable(result);
    calculateAvgTimes(result);
}

bool comparePriority(Process a, Process b) {
    return a.priority < b.priority;
}

void PriorityNonPreemptive(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), comparePriority);
    calculateWaitingTimeFCFS(processes);
    calculateTurnaroundTime(processes);

    std::cout << "Priority Non-Preemptive Scheduling\n";
    printTable(processes);
    calculateAvgTimes(processes);
}

void PriorityPreemptive(std::vector<Process> processes) {
    int n = processes.size();
    int complete = 0, t = 0, min_priority = INT_MAX;
    int highest_priority = 0, finish_time;
    bool check = false;

    for (auto& process : processes) {
        process.remaining_time = process.burst_time;
    }

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((processes[j].arrival_time <= t) && 
                (processes[j].priority < min_priority) && 
                (processes[j].remaining_time > 0)) {
                min_priority = processes[j].priority;
                highest_priority = j;
                check = true;
            }
        }

        if (!check) {
            t++;
            continue;
        }

        processes[highest_priority].remaining_time--;
        min_priority = processes[highest_priority].priority;
        if (processes[highest_priority].remaining_time == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            processes[highest_priority].completion_time = finish_time;
            processes[highest_priority].waiting_time = finish_time - processes[highest_priority].burst_time - processes[highest_priority].arrival_time;
            if (processes[highest_priority].waiting_time < 0) processes[highest_priority].waiting_time = 0;
        }
        t++;
    }

    for (auto& process : processes) {
        process.turnaround_time = process.burst_time + process.waiting_time;
    }

    std::cout << "Priority Preemptive Scheduling\n";
    printTable(processes);
    calculateAvgTimes(processes);
}

int main() {
    int num_processes, choice, quantum;
    do {
        std::cout << "Enter the number of processes: ";
        std::cin >> num_processes;

        std::vector<Process> processes(num_processes);
    
        for (int i = 0; i < num_processes; ++i) {
            processes[i].pid = i + 1;
            std::cout << "Process P" << processes[i].pid << ":\n";
            std::cout << "Enter burst time for process " << i + 1 << ": ";
            std::cin >> processes[i].burst_time;
            std::cout << "Enter arrival time for process " << i + 1 << ": ";
            std::cin >> processes[i].arrival_time;
            std::cout << "Enter priority for process " << i + 1 << ": ";
            std::cin >> processes[i].priority;
            processes[i].remaining_time = processes[i].burst_time;
        }

        std::cout << "Choose Scheduling Algorithm:\n1. FCFS\n2. SJF Non-Preemptive\n3. SJF Preemptive\n4. Round Robin\n5. Priority Non-Preemptive\n6. Priority Preemptive\n7. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                FCFS(processes);
                break;
            case 2:
                SJFNonPreemptive(processes);
                break;
            case 3:
                SJFPreemptive(processes);
                break;
            case 4:
                std::cout << "Enter time quantum for Round Robin: ";
                std::cin >> quantum;
                RoundRobin(processes, quantum);
                break;
            case 5:
                PriorityNonPreemptive(processes);
                break;
            case 6:
                PriorityPreemptive(processes);
                break;
            case 7:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice!";
                break;
        }
    } while (choice != 7);

    return 0;
}
