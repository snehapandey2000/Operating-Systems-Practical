#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;
#define ll long long
#define f(i, n) for (int i = 0; i < n; i++)

void DDA(float x1, float y1, float x2, float y2, int i)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    float steps;
    if (abs(m) <= 1)
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float Delx = dx / steps;
    float Dely = dy / steps;
    float x = x1, y = y1;
    putpixel(round(x), round(y), WHITE);
    for (int k = 1; k <= steps; k++)
    {
        x = x + Delx;
        y = y + Dely;
        putpixel(round(x), round(y), WHITE);
    }
}

void makeRect(int x, int y, int i, int t)
{

    DDA(x, y, t * 10 + x, y, i);
    DDA(x + t * 10, y, t * 10 + x, y + 50, i);
    DDA(x + t * 10, y + 50, x, 50 + y, i);
    DDA(x, y + 50, x, y, i);
}

void intToString(int num, char str[100])
{
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    int num_of_digits = 0, temp = num;
    while (temp)
    {
        ++num_of_digits;
        temp /= 10;
    }
    str[num_of_digits] = '\0';
    temp = num;
    int i = num_of_digits - 1;
    while (temp)
    {
        str[i] = '0' + (temp % 10);
        temp /= 10;
        --i;
    }
}

class Process
{

public:
    int burstTime;
    int num;
    int waitTime;

    Process()
    {
        waitTime = 0;
    }
};

bool cmp(Process p1, Process p2)
{
    return p1.num < p2.num;
}

int main()
{
    initwindow(1300, 800);
    setcolor(WHITE);

    cout << "Enter number of processes : \n";
    int n;
    cin >> n;
    deque<Process> myQueue;
    cout << "Enter the burst times below \n";

    f(i, n)
    {
        cout << "Process " << (i + 1) << "th :";
        Process p;
        p.num = i + 1;
        cin >> p.burstTime;
        myQueue.push_back(p);
    }

    int q;
    cout << "Enter the time quantum : \n";
    cin >> q;

    int x = 100, y = 100;
    int i = 0;
    int prevTime = 0;

    vector<Process> finishedProcesses;

    while (myQueue.size() > 0)
    {
        Process cp = myQueue.front();
        myQueue.pop_front();

        if (cp.burstTime > q)
        {
            int time = q;
            makeRect(x, y, (i % 8) + 1, time);
            char c[3];
            c[0] = 'P';
            c[1] = 48 + cp.num;
            c[2] = '\0';
            outtextxy(x + 5, y + 10, c);

            char c2[100];
            intToString(prevTime, c2);
            outtextxy(x, y + 60, c2);
            x += (time * 10);
            prevTime += time;

            for (auto it = myQueue.begin(); it != myQueue.end(); it++)
            {
                (*it).waitTime += time;
            }
            cp.burstTime = cp.burstTime - time;
            myQueue.push_back(cp);
        }
        else
        {
            int time = cp.burstTime;
            makeRect(x, y, (i % 8) + 1, time);
            char c[3];
            c[0] = 'P';
            c[1] = 48 + cp.num;
            c[2] = '\0';

            outtextxy(x + 5, y + 10, c);

            char c2[100];
            intToString(prevTime, c2);
            outtextxy(x, y + 60, c2);
            x += (time * 10);
            prevTime += (time);

            for (auto it = myQueue.begin(); it != myQueue.end(); it++)
            {
                (*it).waitTime += time;
            }

            finishedProcesses.push_back(cp);
        }

        i++;
    }

    sort(finishedProcesses.begin(), finishedProcesses.end(), cmp);

    double totalWaitingTime = 0;
    cout << "Waiting times\n";
    for (auto c : finishedProcesses)
    {
        cout << "Process P" << c.num << " = " << c.waitTime << endl;
        totalWaitingTime += c.waitTime;
    }

    cout << "\nAverage waiting time = ";
    cout << (totalWaitingTime / n);
    getch();
    return 0;
}
