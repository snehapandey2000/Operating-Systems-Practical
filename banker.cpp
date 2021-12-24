#include <iostream>
using namespace std;

int main()
{

    int n, m, i, j, k;
    int alloc[100][100];
    int max[100][100], avail[100];

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    cout << "Enter \"allocation\" matrix: " << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> alloc[i][j];
        }
    }

    cout << "Enter \"maximum\" demand matrix: " << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> max[i][j];
        }
    }

    cout << "Enter \"available\" matrix: " << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> avail[i];
    }

    int f[100], ans[100], ind = 0;
    for (int k = 0; k < n; k++)
    {
        f[k] = 0;
    }

    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    f[i] = 1;
                }
            }
        }
    }

    cout << "Safe sequence is as follows : <P" << ans[0];
    for (int i = 1; i < n; i++)
    {
        cout << ", P" << ans[i];
    }
    cout << ">" << endl;

    return 0;
}