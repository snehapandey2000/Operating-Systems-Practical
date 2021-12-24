#include <bits/stdc++.h>
using namespace std;
#include <graphics.h>

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

void makeRectangle(int x, int y, int i, int t)
{

    DDA(x, y, t * 10 + x, y, i);
    DDA(x + t * 10, y, t * 10 + x, y + 50, i);
    DDA(x + t * 10, y + 50, x, 50 + y, i);
    DDA(x, y + 50, x, y, i);
}

void int_to_string(int num, char str[100])
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
    int burst_Time;
    int process_num;
    int arrival_time = 0;
    int org_arrival_time;
    int org_burst_time;
    int priority;
};

bool ValueCmp1(Process const &a, Process const &b)
{
    if (a.arrival_time < b.arrival_time)
        return 1;
    else if (a.arrival_time > b.arrival_time)
        return 0;
    else
        return a.priority < b.priority;
}
bool ValueCmp(Process const &a, Process const &b)
{
    return a.priority < b.priority;
}
int main()
{
    initwindow(1100, 800);

    cout << "\n Enter 1 for preemptive priority :\n 2 for non-preemptive priority : \n";
    int choice;
    cin >> choice;

    cout << "\n Enter number of processes :\t";
    int num_task;
    cin >> num_task;

    if (choice == 2)
    {
        Process tasks[num_task];
        cout << "\n Enter the CPU bursts of the processes and their priority : \t";

        int x = 100, y = 100;
        for (int i = 0; i < num_task; i++)
        {
            cout << "\n Enter the CPU burst times and priority of process " << i + 1 << " :\t";
            cin >> tasks[i].burst_Time;
            cin >> tasks[i].priority;
            tasks[i].process_num = i + 1;
        }

        sort(tasks, tasks + num_task, ValueCmp);
        for (int i = 0; i < num_task; i++)
        {
            makeRectangle(x, y, (i % 8) + 1, tasks[i].burst_Time);
            char str[3];
            str[0] = 'P';
            str[1] = '0' + tasks[i].process_num;
            outtextxy(x + 5, y + 10, str);
            x += tasks[i].burst_Time * 10;
        }

        int waiting_time = 0;
        int sum_waiting_time = 0;

        x = 100, y = 100;
        for (int i = 0; i < num_task; i++)
        {
            sum_waiting_time += waiting_time;
            cout << "\n Waiting time for " << tasks[i].process_num << " task is:\t" << waiting_time << " secs";
            makeRectangle(x, y, (i % 8) + 3, tasks[i].burst_Time);
            delay(500);
            char str[100];
            int_to_string(waiting_time, str);
            outtextxy(x + 5, y + 65, str);
            x += (tasks[i].burst_Time) * 10;

            waiting_time += tasks[i].burst_Time;
        }

        cout << "\n\n Average waiting time : \t" << float(sum_waiting_time) / num_task << " secs.";
        getch();
    }

    else
    {
        Process tasks[num_task];
        cout << "\n Enter the CPU bursts of the processes:\t";
        int waiting_time = 0;

        int x = 100, y = 100;
        for (int i = 0; i < num_task; i++)
        {
            cout << "\n Enter the CPU burst of process and arrival time and priority of process " << i + 1 << " :\t";
            cin >> tasks[i].burst_Time;
            cin >> tasks[i].arrival_time;
            cin >> tasks[i].priority;
            tasks[i].process_num = i + 1;
            tasks[i].org_arrival_time = tasks[i].arrival_time;
            tasks[i].org_burst_time = tasks[i].burst_Time;
        }
        sort(tasks, tasks + num_task, ValueCmp1);
        char arr[100];
        int_to_string(tasks[0].arrival_time, arr);
        outtextxy(x + 5, y + 65, arr);

        for (int i = 0; 1; i++)
        {
            if (tasks[0].burst_Time >= 30000)
                break;

            makeRectangle(x, y, tasks[0].process_num, 5);

            char str[3];
            str[0] = 'P';
            str[1] = '0' + tasks[0].process_num;
            str[2] = '\0';
            outtextxy(x + 1, y + 10, str);
            x += 50;
            tasks[0].burst_Time -= 1;
            tasks[0].arrival_time += 1;
            for (int j = 0; j < num_task; j++)
                if (tasks[j].arrival_time < tasks[0].arrival_time)
                    tasks[j].arrival_time = tasks[0].arrival_time;

            char arr[100];
            int_to_string(tasks[0].arrival_time, arr);
            outtextxy(x + 5, y + 65, arr);

            if (tasks[0].burst_Time == 0)
            {
                tasks[0].burst_Time = 300000;
                char arr[2];
                arr[0] = i + '0' + 1;
                arr[1] = '\0';
                outtextxy(x + 1, y + 10, arr);
                cout << "Waiting time for process " << tasks[0].process_num << " is :\t" << (tasks[0].arrival_time - tasks[0].org_arrival_time) - tasks[0].org_burst_time << "secs" << endl;
                waiting_time += (tasks[0].arrival_time - tasks[0].org_arrival_time) - tasks[0].org_burst_time;

                tasks[0].arrival_time = 300000;
                tasks[0].priority = 300000;
            }

            sort(tasks, tasks + num_task, ValueCmp1);
        }
        cout << "\n Average waiting time :\t" << float(waiting_time) / num_task << " secs";
    }
    getch();
    return 0;
}

/*
Sample Input (non preemptive)
10 3
4 1
3 4
6 5
5 2
*/

/**
Sample Input (preemptive)
1
3
5 2 3
4 4 1
2 3 3

**/
