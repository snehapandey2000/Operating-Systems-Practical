#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

#define ll long long
#define f(i, n) for (int i = 0; i < n; i++)

void DDA(float x1, float y1, float x2, float y2, int color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    // Finding slope
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

int wf = 10; //width factor
int h = 50;

//x y top rigth
void makeRectangle(int x, int y, int t, int color) //t is thickness i,e, time
{
    //4 points
    // a---------b
    // |         |
    // |         |
    // d---------c

    int ax = x, ay = y;
    int bx = ax + (t * wf), by = ay;
    int cx = bx, cy = by + h;
    int dx = ax, dy = cy;

    DDA(ax, ay, bx, by, color);
    DDA(bx, by, cx, cy, color);
    DDA(cx, cy, dx, dy, color);
    DDA(dx, dy, ax, ay, color);
}

//to print on graphics window
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

void solve()
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /* Don't forget to take inputs of variable */

    ll t = 1;
    /*is Single Test case?*/ cin >> t;
    while (t--)
    {
        solve();
        cout << "\n";
    }
    return 0;
}