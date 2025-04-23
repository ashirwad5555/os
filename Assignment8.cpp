#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

// Function to calculate total head movement for FIFO
void fifo(vector<int> requests, int head)
{
    int totalMovement = 0;
    cout << "FIFO Order: ";
    for (int req : requests)
    {
        cout << req << " ";
        totalMovement += abs(req - head);
        head = req;
    }
    cout << "\nTotal Head Movement: " << totalMovement << endl;
}

// Function to calculate total head movement for SSTF
void sstf(vector<int> requests, int head)
{
    int totalMovement = 0;
    cout << "SSTF Order: ";
    while (!requests.empty())
    {
        auto closest = min_element(requests.begin(), requests.end(),
                                   [head](int a, int b)
                                   { return abs(a - head) < abs(b - head); });
        cout << *closest << " ";
        totalMovement += abs(*closest - head);
        head = *closest;
        requests.erase(closest);
    }
    cout << "\nTotal Head Movement: " << totalMovement << endl;
}

// Function to calculate total head movement for SCAN
void scan(vector<int> requests, int head, int diskSize, bool direction)
{
    int totalMovement = 0;
    requests.push_back(0);            // Add start of disk
    requests.push_back(diskSize - 1); // Add end of disk
    sort(requests.begin(), requests.end());

    auto it = lower_bound(requests.begin(), requests.end(), head);
    vector<int> left(requests.begin(), it);
    vector<int> right(it, requests.end());

    cout << "SCAN Order: ";
    if (direction)
    { // Moving towards the right
        for (int req : right)
        {
            cout << req << " ";
            totalMovement += abs(req - head);
            head = req;
        }
        for (auto rit = left.rbegin(); rit != left.rend(); ++rit)
        {
            cout << *rit << " ";
            totalMovement += abs(*rit - head);
            head = *rit;
        }
    }
    else
    { // Moving towards the left
        for (auto rit = left.rbegin(); rit != left.rend(); ++rit)
        {
            cout << *rit << " ";
            totalMovement += abs(*rit - head);
            head = *rit;
        }
        for (int req : right)
        {
            cout << req << " ";
            totalMovement += abs(req - head);
            head = req;
        }
    }
    cout << "\nTotal Head Movement: " << totalMovement << endl;
}

// Function to calculate total head movement for C-SCAN
void cscan(vector<int> requests, int head, int diskSize)
{
    int totalMovement = 0;
    requests.push_back(0);            // Add start of disk
    requests.push_back(diskSize - 1); // Add end of disk
    sort(requests.begin(), requests.end());

    auto it = lower_bound(requests.begin(), requests.end(), head);
    vector<int> left(requests.begin(), it);
    vector<int> right(it, requests.end());

    cout << "C-SCAN Order: ";
    for (int req : right)
    {
        cout << req << " ";
        totalMovement += abs(req - head);
        head = req;
    }
    if (!left.empty())
    {
        totalMovement += abs(diskSize - 1 - head); // Move to the end of the disk
        head = 0;                                  // Jump to the start of the disk
        totalMovement += diskSize - 1;             // Add the jump movement
        for (int req : left)
        {
            cout << req << " ";
            totalMovement += abs(req - head);
            head = req;
        }
    }
    cout << "\nTotal Head Movement: " << totalMovement << endl;
}

int main()
{
    int n, head, diskSize, choice;
    bool direction;

    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the requests: ";
    for (int i = 0; i < n; i++)
    {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "Enter the disk size: ";
    cin >> diskSize;

    cout << "Choose the algorithm:\n1. FIFO\n2. SSTF\n3. SCAN\n4. C-SCAN\n";
    cin >> choice;

    if (choice == 3)
    {
        cout << "Enter the direction (1 for right, 0 for left): ";
        cin >> direction;
    }

    switch (choice)
    {
    case 1:
        fifo(requests, head);
        break;
    case 2:
        sstf(requests, head);
        break;
    case 3:
        scan(requests, head, diskSize, direction);
        break;
    case 4:
        cscan(requests, head, diskSize);
        break;
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
