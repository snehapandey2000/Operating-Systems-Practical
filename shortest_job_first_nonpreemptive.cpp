#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

#define ll long long
#define f(i, n) for (int i = 0; i < n; i++)

void DDA(float x1, float y1, float x2, float y2, int color)
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
    putpixel(round(x), round(y), color);
    for (int k = 1; k <= steps; k++)
    {
        x = x + Delx;
        y = y + Dely;
        putpixel(round(x), round(y), color);
    }
}

int wf = 10;
int h = 50;

void makeRectangle(int x, int y, int t, int color)
{

    int ax = x, ay = y;
    int bx = ax + (t * wf), by = ay;
    int cx = bx, cy = by + h;
    int dx = ax, dy = cy;

    DDA(ax, ay, bx, by, color);
    DDA(bx, by, cx, cy, color);
    DDA(cx, cy, dx, dy, color);
    DDA(dx, dy, ax, ay, color);
}

void print(int x, int y, string s)
{
    int n = s.length();
    char c[n + 1];
    for (int i = 0; i < n; i++)
    {
        c[i] = s[i];
    }
    c[n] = '\0';
    outtextxy(x, y, c);
}

class process
{
public:
    int burst;
    string name;
};

bool compare(process p1, process p2)
{
    return (p1.burst < p2.burst);
}
int main()
{
    initwindow(800, 800);
    setcolor(WHITE);
    cout << "Enter the number of processes\n";
    int n;
    cin >> n;
    process allProcesses[n];
    cout << "Enter the burst times \n";
    f(i, n)
    {
        cout << "Process " << (i + 1) << "th :";
        allProcesses[i].name = "P" + to_string(i + 1);
        cin >> allProcesses[i].burst;
    }

    sort(allProcesses, allProcesses + n, compare);

    int x = 100, y = 100;
    f(i, n)
    {
        makeRectangle(x, y, allProcesses[i].burst, 15);

        print(x + 5, y + 10, allProcesses[i].name);

        x += allProcesses[i].burst * wf;
    }

    int waitingTimes[n];
    int turnaround = 0;
    float avgWait = 0;

    x = 100, y = 100;
    f(i, n)
    {
        cout << "For process " << (i + 1) << "\n";
        turnaround += allProcesses[i].burst;

        cout << "waiting time : ";
        waitingTimes[i] = (turnaround - allProcesses[i].burst);
        cout << waitingTimes[i];
        avgWait += waitingTimes[i];
        cout << endl
             << endl;

        makeRectangle(x, y, allProcesses[i].burst, 13);
        delay(500);

        print(x, y + h + 15, to_string(waitingTimes[i]));
        x += allProcesses[i].burst * wf;
    }

    avgWait = avgWait / n;
    cout << "Avg wait time: " << avgWait << endl;
    getch();
    return 0;
}

/*
Sample Input
5
20
15
6
10
12
*/