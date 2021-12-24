#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i, n) for (int i = 0; i < n; i++)

class block
{
public:
    int num;
    int totalSize;
    int size;

    block() {}
    block(int num, int totalSize, int size)
        : num(num), totalSize(totalSize), size(size)
    {
    }
};

class process
{
public:
    int num;
    int size;
    int blockNum;

    process() {}

    process(int num, int size)
        : num(num), size(size), blockNum(-1)
    {
    }
};

bool cmpBestFit(block b1, block b2)
{
    if (b1.size != b2.size)
        return (b1.size < b2.size);

    return (b1.num < b2.num);
}

void printProcesses(process allProcesses[], int numProcesses, block allBlocks[], int numBlocks)
{
    cout << "Process no.\tProcess Size\tBlock Allocated\n";
    for (int i = 0; i < numProcesses; i++)
    {
        cout << allProcesses[i].num << "\t\t" << allProcesses[i].size << "\t\t\t";

        if (allProcesses[i].blockNum == -1)
        {
            cout << "Unallocated\n";
        }
        else
        {
            cout << allProcesses[i].blockNum << "\n";
        }
    }
    cout << "\n\n";
    cout << "Block no.\tBlock Size\t\tStatus\t\tInternal Fragmentation\n";
    for (int i = 0; i < numBlocks; i++)
    {
        cout << allBlocks[i].num << "\t\t" << allBlocks[i].totalSize << "\t\t\t";

        if ((allBlocks[i].totalSize == allBlocks[i].size))
        {
            cout << "Free"
                 << "\t\t\t"
                 << "NA";
        }
        else
        {
            cout << "Busy"
                 << "\t\t\t" << (allBlocks[i].size);
        }
        cout << "\n";
    }
}

int main()
{
    int numBlocks;
    cout << "enter no. of blocks : ";
    cin >> numBlocks;

    block allBlocks[numBlocks];
    cout << "Enter no. and size of blocks :\n";
    f(i, numBlocks)
    {
        cin >> allBlocks[i].num >> allBlocks[i].size;
        allBlocks[i].totalSize = allBlocks[i].size;
    }

    int numProcesses;
    cout << "\nEnter no. of processes : ";
    cin >> numProcesses;
    process allProcesses[numProcesses];
    cout << "Enter no. and size of processes : \n";
    f(i, numProcesses)
    {
        cin >> allProcesses[i].num >> allProcesses[i].size;
    }

    cout << "Choose the algo from below : ";
    cout << "1 for first fit\n";
    cout << "2 for best fit\n";
    cout << "3 for worst fit\n\n";
    int c;
    cin >> c;
    if (c == 1)
    {
        cout << "\nFirst fit\n\n";
        for (int i = 0; i < numProcesses; i++)
        {
            int f = 0;
            for (int j = 0; j < numBlocks; j++)
            {
                if (allBlocks[j].size > 0 && allBlocks[j].size >= allProcesses[i].size)
                {

                    allProcesses[i].blockNum = allBlocks[j].num;
                    allBlocks[j].size -= allProcesses[i].size;
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                allProcesses[i].blockNum = -1;
            }
        }
        printProcesses(allProcesses, numProcesses, allBlocks, numBlocks);

        cout << "\n---------------------------------------------\n\n";
    }
    else if (c == 2)
    {
        cout << "Best fit\n\n";

        sort(allBlocks, allBlocks + numBlocks, cmpBestFit);

        for (int i = 0; i < numProcesses; i++)
        {
            int f = 0;
            for (int j = 0; j < numBlocks; j++)
            {

                if (allBlocks[j].size >= allProcesses[i].size)
                {
                    allProcesses[i].blockNum = allBlocks[j].num;
                    allBlocks[j].size -= allProcesses[i].size;
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                allProcesses[i].blockNum = -1;
            }

            sort(allBlocks, allBlocks + numBlocks, cmpBestFit);
        }
        printProcesses(allProcesses, numProcesses, allBlocks, numBlocks);
        cout << "\n---------------------------------------------\n\n";
    }
    else if (c == 3)
    {
        cout << "Worst fit\n\n";
        sort(allBlocks, allBlocks + numBlocks, cmpBestFit);

        for (int i = 0; i < numProcesses; i++)
        {
            if (allBlocks[numBlocks - 1].size >= allProcesses[i].size)
            {
                allProcesses[i].blockNum = allBlocks[numBlocks - 1].num;
                allBlocks[numBlocks - 1].size -= allProcesses[i].size;
            }
            else
            {
                allProcesses[i].blockNum = -1;
            }
            sort(allBlocks, allBlocks + numBlocks, cmpBestFit);
        }

        printProcesses(allProcesses, numProcesses, allBlocks, numBlocks);
        cout << "\n---------------------------------------------\n\n";
    }
    cout << "\n\n";
    cout << "\n---------------------------------------------\n\n";

    return 0;
}

/*
Sample Input1
5
1 400
2 500
3 300
4 200
5 100 

Sample Input2
5
1 88
2 192
3 277
4 365
5 489 
*/
