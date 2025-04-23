#include <iostream>

using namespace std;

int P, R;

bool isSafe(int allocated[][20], int available[], int max[][20])
{
    int safeSequence[20];
    int work[20];
    int need[20][20];
    bool finish[20] = {false};

    // copy availabe to working array
    for (int j = 0; j < R; j++)
    {
        work[j] = available[j];
    }

    // need = max - allocated
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    // if remaining need[i] <= available , free allcated resurses and mark the process[i] done.
    int count = 0;

    while (count < P)
    {

        bool found = false;
        for (int i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < R; j++)
                {

                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    // free allcated resurses and mark the process[i] done.
                    for (int j = 0; j < R; j++)
                    {
                        work[j] += allocated[i][j];
                    }
                    found = true;
                    finish[i] = true;
                    safeSequence[count++] = i;
                }
            }
        }

        if (!found)
        {
            cout << "no possible safeSequence" << endl;
            return false;
        }
    }

    // print safe sequence
    for (int j = 0; j < P; j++)
    {
        cout << "P" << safeSequence[j] << " ";
    }

    cout << endl;
    return true;
}

int main()
{
    int allocated[20][20];
    int available[20];
    int max[20][20];

    cout << "Enter the no. of processes: ";
    cin >> P;

    cout << "Enter no. of resources : ";
    cin >> R;

    // take allocation matrix
    cout << "Enter alloation matrix" << endl;
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cin >> allocated[i][j];
        }
    }

    // take max needed matrix
    cout << "Enter max need matrix" << endl;
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cin >> max[i][j];
        }
    }

    // take available array
    cout << "Enter available array" << endl;
    for (int j = 0; j < R; j++)
    {
        cin >> available[j];
    }

    // call to isSafe()
    isSafe(allocated, available, max);

    return 0;
}