#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// helper functions
bool search(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        if (frames[i] == key)
            return true;
    }

    return false;
}

int findPagePos(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        if (frames[i] == key)
            return i;
    }

    return -1;
}

int findLRUpos(vector<int> &time)
{
    int min_time = time[0], lru_pos = 0;
    for (int i = 1; i < time.size(); i++)
    {
        if (time[i] < min_time)
        {
            min_time = time[i];
            lru_pos = i;
        }
    }

    return lru_pos;
}

void FCFS(vector<int> &pages, int capacity)
{
    vector<int> frames;
    int page_fault = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        if (!search(pages[i], frames))
        {
            // page fault
            if (frames.size() == capacity)
            {
                int pos = 0; // fcfs 0th page in the frame is replaced
                frames[pos] = pages[i];
            }
            else
            {

                frames.push_back(pages[i]);
            }

            page_fault++;
        }
        else
        {
            // page hit
        }

        cout << "frame content : ";
        for (int i = 0; i < frames.size(); i++)
        {
            cout << frames[i] << " ";
        }
    }

    cout << "total page faults" << page_fault << endl;
}

void LRU(vector<int> &pages, int capacity)
{
    vector<int> frames;
    vector<int> access_time;
    int page_fault = 0;
    int current_time = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        current_time++;
        if (!search(pages[i], frames))
        {
            // page fault
            if (frames.size() == capacity)
            {
                int pos = findLRUpos(access_time);
                frames[pos] = pages[i];
                access_time[pos] = current_time;
            }
            else
            {

                frames.push_back(pages[i]);
                access_time.push_back(current_time);
            }

            page_fault++;
        }
        else
        {
            // page hit just update the access_timing
            access_time[findPagePos(pages[i], frames)] = current_time;
        }

        cout << "frame content : ";
        for (int i = 0; i < frames.size(); i++)
        {
            cout << frames[i] << " ";
        }
    }
}

int main()
{
    int n, capacity;
    cout << "Enter the capcity of frame" << endl;
    cin >> capacity;
    cout << "Enter the pages count" << endl;
    cin >> n;

    cout << "Enter the pages." << endl;
    vector<int> pages(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    // call for FCFS
    // FCFS(pages, capacity);

    // call for LRU
    LRU(pages, capacity);
}
