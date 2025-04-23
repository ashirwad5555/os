#include <bits/stdc++.h>
using namespace std;

void firstFit(int block[], int process[], int m, int n, int allocation[])
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0; j <m;j++)
        {
            if(block[j] >= process[i])
            {
                allocation[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    //print the allocation of block

    for(int i = 0 ; i < m ;i++)
    {
        cout<<allocation[i]<<"is allocated to block"<<i+1<<endl;
    }
}

int main()
{
    int m,n;

    cout<<"Enter the number of blocks: ";
    cin>>m;
    cout<<"Enter the number of processes: ";
    cin>>n;

    int block[m],process[n],allocation[n];

    cout<<"Enter the size of blocks:\n";
    for(int i= 0;i<m;i++)
    {
        cout<<"Block "<<i+1<<": ";
        cin>>block[i];
    }

    cout<<"Enter the size of processes:\n";
    for(int i= 0;i<n;i++)
    {
        cout<<"Process "<<i+1<<": ";
        cin>>process[i];
        allocation[i] = -1;
    }


    firstFit(block,process,m,n,allocation);

    return 0;
}