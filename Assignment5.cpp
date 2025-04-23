#include <iostream>
using namespace std;

int P, R; 

bool isSafe(int available[], int max[][20], int allocation[][20]) {
    int need[20][20];
    bool finish[20] = {false};
    int safeSequence[20];
    int work[20];
    
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }
    
    int count = 0;
    
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is in an unsafe state!" << endl;
            return false;
        }
    }
    
    cout << "System is in a safe state. Safe sequence is: ";
    for (int i = 0; i < P; i++) {
        cout << "P" << safeSequence[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    cout << "Enter number of processes: ";
    cin >> P;
    cout << "Enter number of resources: ";
    cin >> R;
    
    int available[20], max[20][20], allocation[20][20];
    
    cout << "Enter available resources: ";
    for (int i = 0; i < R; i++) {
        cin >> available[i];
    }
    
    cout << "Enter Max matrix: " << endl;
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cin >> max[i][j];
        }
    }
    
    cout << "Enter Allocation matrix: " << endl;
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cin >> allocation[i][j];
        }
    }
    
    isSafe(available, max, allocation);
    
    return 0;
}
