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

class Process
{
public:
    int burst_Time;
    int process_num;
    int arrival_time = 0;
    int orignal_arrival_time;
    int orignal_burst_time;
};

bool cmp(Process const &a, Process const &b)
{
    if (a.arrival_time != b.arrival_time)
        return (a.arrival_time < b.arrival_time);
    else
        return a.burst_Time < b.burst_Time;
}
int main()
{
    initwindow(1400, 900);

    cout << "\n Enter the number of processes : ";
    int num_task;
    cin >> num_task;

    cout << "\n We are following preemptive scheduling\n";

    Process tasks[num_task];
    int waiting_time = 0;

    int x = 100, y = 100;
    for (int i = 0; i < num_task; i++)
    {
        cout << "\n Enter CPU burst and arrival time of process " << i + 1 << " :";
        cin >> tasks[i].burst_Time;
        cin >> tasks[i].arrival_time;
        tasks[i].process_num = i + 1;
        tasks[i].orignal_arrival_time = tasks[i].arrival_time;
        tasks[i].orignal_burst_time = tasks[i].burst_Time;
    }

    sort(tasks, tasks + num_task, cmp);
    char arr[100];
    print(x + 5, y + 65, to_string(tasks[0].arrival_time));

    while (1)
    {
        if (tasks[0].burst_Time >= 300000)
            break;

        makeRectangle(x, y, 5, 15);

        print(x + 1, y + 10, "P" + to_string(tasks[0].process_num));
        x += 50;
        tasks[0].burst_Time -= 1;
        tasks[0].arrival_time += 1;

        for (int j = 0; j < num_task; j++)
            if (tasks[j].arrival_time < tasks[0].arrival_time)
                tasks[j].arrival_time = tasks[0].arrival_time;

        if (tasks[0].burst_Time == 0)
        {
            tasks[0].burst_Time = 300000;
            cout << "Waiting time for process " << tasks[0].process_num << " is :\t" << (tasks[0].arrival_time - tasks[0].orignal_arrival_time) - tasks[0].orignal_burst_time << "secs" << endl;
            waiting_time += (tasks[0].arrival_time - tasks[0].orignal_arrival_time) - tasks[0].orignal_burst_time;
        }

        print(x + 5, y + 65, to_string(tasks[0].arrival_time));
        sort(tasks, tasks + num_task, cmp);
    }
    cout << "\n Average waiting time :\t" << float(waiting_time) / num_task << " secs";
    getch();
    return 0;
}

/*
Sample Input1
4
0 8
1 4
2 8
3 2
*/

/*
Sample Input2
3
5 2
4 3
2 4
*/
