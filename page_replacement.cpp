#include <bits/stdc++.h>
using namespace std;

void fifo(int pages[], int n, int capacity)
{
    unordered_set<int> s;
    queue<int> indexes;
    int miss = 0;
    for (int i = 0; i < n; i++)
    {
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                indexes.push(pages[i]);
                miss++;
            }
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                miss++;
            }
        }
    }
    cout << "hits = " << n - miss << endl;
    cout << "misses = " << miss << endl;
    cout << "Page fault ratio = " << (float)miss / n * 100 << "%" << endl;
}
void lru(int pages[], int n, int capacity)
{
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int miss = 0;
    for (int i = 0; i < n; i++)
    {
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                miss++;
            }
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int lru = INT_MAX, val;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
                miss++;
            }
        }
        indexes[pages[i]] = i;
    }
    cout << "hits = " << n - miss << endl;
    cout << "misses = " << miss << endl;
    cout << "Page fault ratio = " << (float)miss / n * 100 << "%" << endl;
}
bool search_for_optimal(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
        if (frames[i] == key)
        {
            return true;
        }
    return false;
}
int predict_for_optimal(int pages[], vector<int> &frames, int n, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
        {
            return i;
        }
    }
    return res;
}
void optimal(int pages[], int n, int capacity)
{
    vector<int> frames;
    int hit = 0;
    for (int i = 0; i < n; i++)
    {
        if (search_for_optimal(pages[i], frames))
        {
            hit++;
            continue;
        }

        if (frames.size() < capacity)
        {
            frames.push_back(pages[i]);
        }
        else
        {
            int j = predict_for_optimal(pages, frames, n, i + 1);
            frames[j] = pages[i];
        }
    }
    cout << "hits = " << hit << endl;
    cout << "misses = " << n - hit << endl;
    cout << "Page fault ratio = " << (float)(n - hit) / n * 100 << "%" << endl;
}

int main()
{
    int n, capacity, pages[100];
    cout << "Enter number of pages : ";
    cin >> n;
    cout << "Enter number of frames : ";
    cin >> capacity;
    cout << "Enter page sizes :\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> pages[i];
    }
    cout << endl
         << "Choose from below" << endl;

    cout << "1. First In First Out Page Replacement Algorithm (FIFO)" << endl;
    cout << "2. Least Recently Used Page Replacement Algorithm (LRU)" << endl;
    cout << "3. Optimal Page Replacement Algorithm" << endl;
    int option;
    cout << endl;
    cout << "Enter choice : ";
    cin >> option;
    cout << endl;
    if (option == 1)
    {
        fifo(pages, n, capacity);
    }
    else if (option == 2)
    {
        lru(pages, n, capacity);
    }
    else
    {
        optimal(pages, n, capacity);
    }
    return 0;
}

/*
Sample Inputs
20
4
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
1

20
4
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
2

20
4
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
3
*/
