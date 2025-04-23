#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if a page exists in memory frames
bool search(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
        if (frames[i] == key)
            return true;
    return false;
}

// Function to find the position of a page in frames
int findPagePosition(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
        if (frames[i] == key)
            return i;
    return -1; // Page not found
}

// Function to find the position to be replaced using FCFS
int findOldestPage(vector<int> &frames)
{
    // In FCFS, the oldest page is always at index 0
    return 0;
}

// Function to find the position to be replaced using LRU
int findLRU(vector<int> &time)
{
    int lru = 0, min_time = time[0];
    for (int i = 1; i < time.size(); i++)
    {
        if (time[i] < min_time)
        {
            min_time = time[i];
            lru = i;
        }
    }
    return lru;
}

// The Core Idea
// The Optimal algorithm says: "When you need to replace a page, pick the one that won't be needed for the longest time in the future."

// How It Works (Step by Step)
// For each page reference:

// Check if the page is already in memory
// If yes → page hit → do nothing
// If no → page fault → need to handle it
// When a page fault happens:

// If frames aren't full → simply add the page
// If frames are full → need to replace a page
// To choose which page to replace:

// Look at all future page references
// For each page in memory, find when it will be used next
// Choose the page that will NOT be used for the longest time
// If a page won't be used again, replace it immediately

// Function to find the page that will not be used for the longest time in the future
int findOptimalPage(vector<int> &frames, vector<int> &pages, int current_index)
{
    int farthest = -1, farthest_index = -1;

    // Check each page in frame
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        bool found = false;

        // Find when this page will be used next
        for (j = current_index + 1; j < pages.size(); j++)
        {
            if (frames[i] == pages[j])
            {
                found = true;
                if (j > farthest)
                {
                    farthest = j;
                    farthest_index = i;
                }
                break;
            }
        }

        // If page will not be used in future, return its index immediately
        if (!found)
            return i;
    }

    // If all pages will be used in future, return the one used farthest in the future
    return (farthest_index == -1) ? 0 : farthest_index;
}

// Function to implement FCFS page replacement
void fcfs(vector<int> &pages, int capacity)
{
    cout << "\nFCFS Page Replacement Algorithm\n";

    vector<int> frames;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        cout << "Reference: " << pages[i] << " -> ";

        // If the page is not present in memory
        if (!search(pages[i], frames))
        {
            page_faults++;
            // If frames are full, replace the oldest page (FCFS logic)
            if (frames.size() == capacity)
            {
                int pos = findOldestPage(frames);
                cout << "Page fault! Replace " << frames[pos] << " with " << pages[i] << endl;
                frames[pos] = pages[i];
            }
            else
            {
                // If frames are not full, add the page
                cout << "Page fault! Add to empty frame" << endl;
                frames.push_back(pages[i]);
            }
        }
        else
        {
            cout << "Page hit!" << endl;
        }

        // Display the current state of frames
        cout << "Frames: ";
        for (int j = 0; j < frames.size(); j++)
        {
            cout << frames[j] << " ";
        }
        cout << endl;
    }

    cout << "\nTotal Page Faults (FCFS): " << page_faults << endl;
    cout << "Page Fault Rate: " << (float)page_faults / pages.size() * 100 << "%" << endl;
}

// Function to implement LRU page replacement - improved version
void lru(vector<int> &pages, int capacity)
{
    cout << "\nLRU Page Replacement Algorithm\n";

    vector<int> frames;      // To store pages in memory
    vector<int> access_time; // To store the last access time of each page
    int page_faults = 0;
    int current_time = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        current_time++;
        cout << "Reference: " << pages[i] << " -> ";

        // Find if page already exists in memory
        int page_pos = findPagePosition(pages[i], frames);

        // Page not in memory - need to handle page fault
        if (page_pos == -1)
        {
            page_faults++;
            // If frames are full, replace the least recently used page
            if (frames.size() == capacity)
            {
                int lru_pos = findLRU(access_time);
                cout << "Page fault! Replace " << frames[lru_pos] << " with " << pages[i] << endl;
                frames[lru_pos] = pages[i];
                access_time[lru_pos] = current_time;
            }
            else
            {
                // If frames are not full, add the page
                cout << "Page fault! Add to empty frame" << endl;
                frames.push_back(pages[i]);
                access_time.push_back(current_time);
            }
        }
        else
        {
            // Page is already in memory - update access time
            cout << "Page hit!" << endl;
            access_time[page_pos] = current_time;
        }

        // Display the current state of frames
        cout << "Frames: ";
        for (int j = 0; j < frames.size(); j++)
        {
            cout << frames[j] << " ";
        }
        cout << endl;

        // Optional: Display the access times for debugging
        /*
        cout << "Times: ";
        for (int j = 0; j < access_time.size(); j++)
        {
            cout << access_time[j] << " ";
        }
        cout << endl;
        */
    }

    cout << "\nTotal Page Faults (LRU): " << page_faults << endl;
    cout << "Page Fault Rate: " << (float)page_faults / pages.size() * 100 << "%" << endl;
}

// Function to implement Optimal page replacement
void optimal(vector<int> &pages, int capacity)
{
    cout << "\nOptimal Page Replacement Algorithm\n";

    vector<int> frames;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        cout << "Reference: " << pages[i] << " -> ";

        // If the page is not present in memory
        if (!search(pages[i], frames))
        {
            // If frames are full, replace the page that won't be used for the longest time
            if (frames.size() == capacity)
            {
                int pos = findOptimalPage(frames, pages, i);
                cout << "Page fault! Replace " << frames[pos] << " with " << pages[i] << endl;
                frames[pos] = pages[i];
            }
            else
            {
                // If frames are not full, add the page
                cout << "Page fault! Add to empty frame" << endl;
                frames.push_back(pages[i]);
            }
            page_faults++;
        }
        else
        {
            cout << "Page hit!" << endl;
        }

        // Display the current state of frames
        cout << "Frames: ";
        for (int j = 0; j < frames.size(); j++)
        {
            cout << frames[j] << " ";
        }
        cout << endl;
    }

    cout << "\nTotal Page Faults (Optimal): " << page_faults << endl;
    cout << "Page Fault Rate: " << (float)page_faults / pages.size() * 100 << "%" << endl;
}

int main()
{
    int n, capacity, choice;

    cout << "Enter the number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference sequence: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter the number of frames: ";
    cin >> capacity;

    cout << "Choose the page replacement algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. LRU\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        fcfs(pages, capacity);
        break;
    case 2:
        lru(pages, capacity);
        break;
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}