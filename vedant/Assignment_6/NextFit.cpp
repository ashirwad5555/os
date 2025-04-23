#include <bits/stdc++.h>
using namespace std;

// Global variable to remember the last position
int lastIndex = 0;

void nextFit(int blockSize[], int m, int processSize[], int n, int allocation[])
{
    // // Initialize all allocations as -1 (not allocated)
    // for (int i = 0; i < n; i++)
    //     allocation[i] = -1;

    // For each process
    for (int i = 0; i < n; i++)
    {
        // Start from the last allocated position
        int j = lastIndex;
        bool allocated = false;

        // Count how many blocks we've checked to avoid infinite loop
        int count = 0;

        // Search through all blocks once, starting from lastIndex
        while (count < m && !allocated)
        {
            if (blockSize[j] >= processSize[i])
            {
                // Allocate this block to process i
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastIndex = (j + 1) % m; // Move to next position
                allocated = true;
                break;
            }
            j = (j + 1) % m; // Move to next block cyclically
            count++;         // Increment count of blocks checked
        }

        // If we couldn't allocate, the process remains unallocated (-1)
    }
    // Display allocation details
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

int main()
{
    int m, n;

    cout << "Enter the number of blocks: ";
    cin >> m;
    cout << "Enter the number of processes: ";
    cin >> n;

    int blockSize[m], processSize[n], allocation[n];

    cout << "Enter the size of each block: ";
    for (int i = 0; i < m; i++)
    {
        cin >> blockSize[i];
    }

    cout << "Enter the size of each process: ";
    for (int i = 0; i < n; i++)
    {
        cin >> processSize[i];
    }

    // Initialize all allocations as -1 (not allocated)
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    nextFit(blockSize, m, processSize, n, allocation);

    return 0;
}