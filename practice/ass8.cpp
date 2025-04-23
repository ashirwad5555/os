#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void FIFO(vector<int> &requests, int head)
{
    int headMovementCount = 0;

    for (int req : requests)
    {

        headMovementCount += abs(req - head);
        head = req;
    }

    cout << "headmovement count: " << headMovementCount;
}

void SSTF(vector<int> &requests, int head)
{
    int headMovementCount = 0;

    while (!requests.empty())
    {

        auto closest = min_element(requests.begin(), requests.end(), [head](int a, int b)
                                   { return abs(a - head) < abs(b - head); });

        headMovementCount += abs((*closest) - head);
        head = *closest;

        requests.erase(closest);
    }

    cout << "headmovement count" << headMovementCount << endl;
}

void SCAN(vector<int> &requests, int head, int disk_size, int direction)
{
    // elevator algorithm

    int headMovementCount = 0;
    requests.push_back(0);
    requests.push_back(disk_size - 1);

    sort(requests.begin(), requests.end());

    auto it = lower_bound(requests.begin(), requests.end(), head);

    vector<int> left(requests.begin(), it);
    vector<int> right(it, requests.end());

    if (direction) // 1 for towords right from head
    {
        for (auto req : right)
        {
            headMovementCount += abs(req - head);
            head = req;
        }

        for (auto rit = left.rbegin(); rit != left.rend(); ++rit)
        {
            headMovementCount += abs(head - (*rit));
            head = *rit;
        }
    }
    else
    {
        // 0 towords left

        for (auto rit = left.rbegin(); rit != left.rend(); ++rit)
        {
            cout << *rit << " ";
            headMovementCount += abs(*rit - head);
            head = *rit;
        }
        for (int req : right)
        {
            cout << req << " ";
            headMovementCount += abs(req - head);
            head = req;
        }
    }

    cout << "head count : " << headMovementCount << endl;
}

void CSCAN(vector<int> &requests, int head, int disk_size)
{
    int headMovementCount = 0;
    requests.push_back(0);
    requests.push_back(disk_size - 1);

    sort(requests.begin(), requests.end());

    auto it = lower_bound(requests.begin(), requests.end(), head);

    vector<int> left(requests.begin(), it);
    vector<int> right(it, requests.end());

    // FIRST GO TO RIGHT THEN TO O THEN COVER LEFT VECTOR
    for (auto req : right)
    {
        headMovementCount += abs(req - head);
        head = req;
    }

    if (!left.empty())
    {
        headMovementCount += abs((disk_size - 1) - head); // reached to end
        head = 0;                                      // jumped to starting
        headMovementCount += (disk_size - 1);          // jump count added

        // traverse the left part
        for (int req : left)
        {
            cout << req << " ";
            headMovementCount += abs(req - head);
            head = req;
        }
    }

    cout << "head count movement : " << headMovementCount << endl;
}

int main()
{

    int n, head, diskSize, choice;
    bool direction = 1;

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

    // FIFO(requests, head);
    // SSTF(requests, head);
    // SCAN(requests, head, diskSize, direction);
    CSCAN(requests, head, diskSize);
}