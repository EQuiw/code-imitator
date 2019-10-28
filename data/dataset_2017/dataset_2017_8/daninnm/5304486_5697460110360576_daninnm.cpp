#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

long long t, n, p;
long long r[64];
long long q[64][64];
long long ti[64];

inline long long inrange(long long req, long long cur)
{
    if (cur * 10 < 9 * req) return -1;
    if (cur * 10 > 11 * req) return 1;
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);

    freopen("in.in","r",stdin);
    freopen("out2.out","w",stdout);
    //*/
    cin >> t;
    for(int id = 0; id < t; ++id)
    {
        int ans = 0;
        cin >> n >> p;
        for (int i = 0; i < n; ++i) {ti[i] = 0;}
        for (int i = 0; i < n; ++i) cin >> r[i];
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < p; ++j) cin >> q[i][j];
        }
        for (int i = 0; i < n; ++i)
        {
            sort(q[i], q[i] + p);
        }
        /*for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < p; ++j) cout << q[i][j] << " ";
            cout << "\n";
        }//*/
        long long meals = 1;/*
        for (int i = 0; i < p; ++i)
        {
            ti[0] = i;*/

            for (meals = 1; meals < 1000000; ++meals)
            {
                //cout << q[0][0];
                //cout << "M: " << meals << "\n";
                for (int j = 0; j < n; ++j)
                {
                    while (ti[j] < p && inrange(meals * r[j], q[j][ti[j]]) < 0){ ++ti[j]; }
                }
                int j;
                for (j = 0; j < n; ++j)
                {
                    //cout << meals * r[j] << " " << q[j][ti[j]] << "\n";
                    if (ti[j] >= p || inrange(meals * r[j], q[j][ti[j]]) != 0) break;
                }
                if (j == n)
                {
                    ++ans; meals--;
                    //cout << meals << " : ";
                    for (j = 0; j < n; ++j)
                    {
                        //cout << ti[j] << " ";
                        ++ti[j];
                    }
                    //cout << "\n";
                }
            }
        //}

        cout << "Case #" << id + 1 << ": " << ans << "\n";

    }

    return 0;
}
/*
6
2 1
500 300
900
660
2 1
500 300
1500
809
2 2
50 100
450 449
1100 1101
2 1
500 300
300
500
1 8
10
11 13 17 11 16 14 12 18
3 3
70 80 90
1260 1500 700
800 1440 1600
1700 1620 900
*/
