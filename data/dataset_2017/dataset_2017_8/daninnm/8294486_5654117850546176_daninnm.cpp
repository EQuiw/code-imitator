#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

int T, n;
int rs, os, ys, gs, bs, vs, b, r, y;
bool fb, fr, fy;

void p(char c)
{
    if(c == 'B')
    {
        cout << "B";
        if (fb)
        {
            fb = 0;
            for (int i = 0; i < os; ++i) { cout << "OB"; }
        }
    }
    if(c == 'R')
    {
        cout << "R";
        if (fr)
        {
            fr = 0;
            for (int i = 0; i < gs; ++i) { cout << "GR"; }
        }
    }
    if(c == 'Y')
    {
        cout << "Y";
        if (fy)
        {
            fy = 0;
            for (int i = 0; i < vs; ++i) { cout << "VY"; }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);

    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    //*/
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> n >> rs >> os >> ys >> gs >> bs >> vs;
        b = bs - os;
        r = rs - gs;
        y = ys - vs;
        //cout << b << r << y;
        if (b == 0 && bs != 0 && bs + os != n) { cout << "Case #" << t << ": IMPOSSIBLE\n"; continue; }
        if (r == 0 && rs != 0 && rs + gs != n) { cout << "Case #" << t << ": IMPOSSIBLE\n"; continue; }
        if (y == 0 && ys != 0 && ys + vs != n) { cout << "Case #" << t << ": IMPOSSIBLE\n"; continue; }
        if (b < 0 || r < 0 || y < 0 || b > r + y || r > b + y || y > b + r) { cout << "Case #" << t << ": IMPOSSIBLE\n"; continue; }
        if (b == 0 && bs != 0)
        {
            cout << "Case #" << t << ": ";
            for (int i = 0; i < n/2; ++i) { cout << "BO"; }
            cout << "\n";
            continue;
        }
        if (r == 0 && rs != 0)
        {
            cout << "Case #" << t << ": ";
            for (int i = 0; i < n/2; ++i) { cout << "RG"; }
            cout << "\n";
            continue;
        }
        if (y == 0 && ys != 0)
        {
            cout << "Case #" << t << ": ";
            for (int i = 0; i < n/2; ++i) { cout << "YV"; }
            cout << "\n";
            continue;
        }

        cout << "Case #" << t << ": ";
        fb = 1; fr = 1; fy = 1;
        if (b >= r && b >= y)
        {
            while (true)
            {
                if (r > 0)
                {
                    p('R');
                    --r;
                    if (b > r + y) break;
                }
                if (y > 0)
                {
                    p('Y');
                    --y;
                    if (b > r + y) break;
                }
            }
            p('B');
            --b;
            while (b)
            {
                if (r > 0)
                {
                    p('R');
                    --r;
                }
                else
                {
                    p('Y');
                    --y;
                }
                p('B');
                --b;
            }
            cout << "\n";
            continue;
        }
        if (r >= b && r >= y)
        {
            while (true)
            {
                if (b > 0)
                {
                    p('B');
                    --b;
                    if (r > b + y) break;
                }
                if (y > 0)
                {
                    p('Y');
                    --y;
                    if (r > b + y) break;
                }
            }
            p('R');
            --r;
            while (r)
            {
                if (b > 0)
                {
                    p('B');
                    --b;
                }
                else
                {
                    p('Y');
                    --y;
                }
                p('R');
                --r;
            }
            cout << "\n";
            continue;
        }
        if (y >= r && y >= b)
        {
            while (true)
            {
                if (r > 0)
                {
                    p('R');
                    --r;
                    if (y > r + b) break;
                }
                if (b > 0)
                {
                    p('B');
                    --b;
                    if (y > r + b) break;
                }
            }
            p('Y');
            --y;
            while (y)
            {
                if (r > 0)
                {
                    p('R');
                    --r;
                }
                else
                {
                    p('B');
                    --b;
                }
                p('Y');
                --y;
            }
            cout << "\n";
            continue;
        }
    }

    return 0;
}
