#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i, n) for (int i = 0; i < n; i++)

int main()
{
    cout << "Enter the max size of bounded buffer : ";
    int n;
    cin >> n;

    deque<int> myQueue;
    int element = 0;
    char x;
    while (true)
    {
        cout << "Enter P for producer OR C for consumer OR S for printing the buffer\n";
        cin >> x;

        if (x == 'p' || x == 'P')
        {
            if (myQueue.size() == n)
            {
                cout << "buffer is Full. Please Wait for consumer to consume\n";
            }

            else
            {
                cout << element << " is inserted into the buffer\n";
                myQueue.push_back(element);
                element++;
            }
        }

        else if (x == 'c' || x == 'C')
        {
            if (myQueue.size() == 0)
            {
                cout << "buffer is Empty. Please Wait for producer to produce\n";
            }
            else
            {
                cout << myQueue.front() << " consumed\n";
                myQueue.pop_front();
            }
        }

        else
        {
            for (auto c : myQueue)
                cout << c << " ";

            cout << endl;
        }

        cout << endl;
    }

    return 0;
}
