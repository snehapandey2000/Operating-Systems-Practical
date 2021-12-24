#include <bits/stdc++.h>
using namespace std;

class diningMonitor
{
public:
    int state[5] = {0};
    //0-thinking, 1-hungry 2-eating

    void test(int i)
    {
        if ((state[(i + 4) % 5] != 2) && state[i] == 1 && state[(i + 1) % 5] != 2)
        {
            cout << "Philosopher " << i << " is eating.\n";
            state[i] = 2;
        }
    }

    void pickup(int i)
    {
        state[i] = 1;
        test(i);
        if (state[i] != 2)
        {
            cout << "Philosopher " << i << " remains hungry.\n";
        }
    }

    void putdown(int i)
    {
        cout << "Philosopher " << i << " completed eating and is now in thinking state.\n";
        state[i] = 0;
        test((i + 4) % 5);
        test((i + 1) % 5);
    }
};

int main()
{
    diningMonitor dm;
    char n = 'y';
    while (n != 'n')
    {
        cout << "\n thinking Philosophers :";
        for (int i = 0; i < 5; i++)
            if (dm.state[i] == 0)
                cout << "\t" << i;

        cout << "\n hungry Philosophers:";
        for (int i = 0; i < 5; i++)
            if (dm.state[i] == 1)
                cout << "\t" << i;

        cout << "\n eating philosophers:";
        for (int i = 0; i < 5; i++)
            if (dm.state[i] == 2)
                cout << "\t" << i;
        cout << "\n";

        cout << "\n Enter the philosopher number (0-4) and its action \n 0 for stop eating, 1 for hungry : \n";
        int a, b;
        cin >> a >> b;
        if (b)
            dm.pickup(a);
        else
            dm.putdown(a);

        cout << "\npress y to continue, else press n";
        cin >> n;
    }
    return 0;
}
