#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Block
{
    int size;
    int id;
    bool allocated;
};

struct Process
{
    int size;
    int allocatedBlock;
};

void firstFit(vector<Block> &blocks, vector<Process> &processes)
{
    for (auto &process : processes)
    {
        for (auto &block : blocks)
        {
            if (!block.allocated && block.size >= process.size)
            {
                process.allocatedBlock = block.id;
                block.allocated = true;
                break;
            }
        }
    }
}

void bestFit(vector<Block> &blocks, vector<Process> &processes)
{
    for (auto &process : processes)
    {
        int bestIndex = -1;
        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (!blocks[i].allocated && blocks[i].size >= process.size)
            {
                if (bestIndex == -1 || blocks[i].size < blocks[bestIndex].size)
                {
                    bestIndex = i;
                }
            }
        }
        if (bestIndex != -1)
        {
            process.allocatedBlock = blocks[bestIndex].id;
            blocks[bestIndex].allocated = true;
        }
    }
}

void worstFit(vector<Block> &blocks, vector<Process> &processes)
{
    for (auto &process : processes)
    {
        int worstIndex = -1;
        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (!blocks[i].allocated && blocks[i].size >= process.size)
            {
                if (worstIndex == -1 || blocks[i].size > blocks[worstIndex].size)
                {
                    worstIndex = i;
                }
            }
        }
        if (worstIndex != -1)
        {
            process.allocatedBlock = blocks[worstIndex].id;
            blocks[worstIndex].allocated = true;
        }
    }
}

void nextFit(vector<Block> &blocks, vector<Process> &processes)
{
    int lastAllocatedIndex = 0;
    for (auto &process : processes)
    {
        bool allocated = false;
        for (size_t i = lastAllocatedIndex; i < blocks.size(); i++)
        {
            if (!blocks[i].allocated && blocks[i].size >= process.size)
            {
                process.allocatedBlock = blocks[i].id;
                blocks[i].allocated = true;
                lastAllocatedIndex = i;
                allocated = true;
                break;
            }
        }
        if (!allocated)
        {
            for (size_t i = 0; i < lastAllocatedIndex; i++)
            {
                if (!blocks[i].allocated && blocks[i].size >= process.size)
                {
                    process.allocatedBlock = blocks[i].id;
                    blocks[i].allocated = true;
                    lastAllocatedIndex = i;
                    break;
                }
            }
        }
    }
}

void displayResultsTable(const vector<Process> &processes)
{
    // Print table header with borders
    cout << "\n+------------+---------------+------------------+------------+" << endl;
    cout << "| Process ID | Process Size  | Allocation Status | Block ID   |" << endl;
    cout << "+------------+---------------+------------------+------------+" << endl;

    // Print each process row
    for (size_t i = 0; i < processes.size(); i++)
    {
        cout << "| " << setw(10) << i + 1 << " | "
             << setw(13) << processes[i].size << " | ";

        if (processes[i].allocatedBlock != -1)
            cout << setw(16) << "Allocated" << " | " << setw(10) << processes[i].allocatedBlock << " |" << endl;
        else
            cout << setw(16) << "Not Allocated" << " | " << setw(10) << "-" << " |" << endl;
    }

    cout << "+------------+---------------+------------------+------------+" << endl;
}

int main()
{
    // // Initialize memory blocks and processes
    // vector<Block> blocks = {{100, 1, false}, {500, 2, false}, {200, 3, false}, {300, 4, false}, {600, 5, false}};
    // vector<Process> processes = {{212, -1}, {417, -1}, {112, -1}, {426, -1}};

    // Initialize memory blocks and processes
    vector<Block> blocks = {
        {100, 1, false},
        {500, 2, false},
        {200, 3, false},
        {300, 4, false},
        {600, 5, false}};

    vector<Process> processes = {
        {212, -1},
        {417, -1},
        {112, -1},
        {426, -1}};

    int choice;

    // Display memory blocks
    cout << "\nAvailable Memory Blocks:" << endl;
    cout << "+----------+----------+" << endl;
    cout << "| Block ID | Size     |" << endl;
    cout << "+----------+----------+" << endl;
    for (auto &block : blocks)
    {
        cout << "| " << setw(8) << block.id << " | " << setw(8) << block.size << " |" << endl;
    }
    cout << "+----------+----------+" << endl;

    // Display processes
    cout << "\nProcesses to be allocated:" << endl;
    cout << "+------------+---------------+" << endl;
    cout << "| Process ID | Process Size  |" << endl;
    cout << "+------------+---------------+" << endl;
    for (size_t i = 0; i < processes.size(); i++)
    {
        cout << "| " << setw(10) << i + 1 << " | " << setw(13) << processes[i].size << " |" << endl;
    }

    while (1)
    {
    
    cout << "+------------+---------------+" << endl;

    cout << "\nSelect Memory Allocation Algorithm:" << endl;
    cout << "1. First Fit" << endl;
    cout << "2. Best Fit" << endl;
    cout << "3. Worst Fit" << endl;
    cout << "4. Next Fit" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    // Create copies for allocation
    vector<Block> workingBlocks = blocks;
    vector<Process> workingProcesses = processes;

    // Apply selected algorithm using switch case
    switch (choice)
    {
    case 1:
        cout << "\nApplying First Fit Algorithm...";
        firstFit(workingBlocks, workingProcesses);
        break;
    case 2:
        cout << "\nApplying Best Fit Algorithm...";
        bestFit(workingBlocks, workingProcesses);
        break;
    case 3:
        cout << "\nApplying Worst Fit Algorithm...";
        worstFit(workingBlocks, workingProcesses);
        break;
    case 4:
        cout << "\nApplying Next Fit Algorithm...";
        nextFit(workingBlocks, workingProcesses);
        break;

    case 5:
        cout << "\nExiting program...";
        return 0;    
    default:
        cout << "\nInvalid choice! Defaulting to First Fit...";
        firstFit(workingBlocks, workingProcesses);
    }

    // Display results in tabular format
    displayResultsTable(workingProcesses);
    
}
    return 0;
}
