/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main()
{
    ios::sync_with_stdio(false);
#ifdef HOME
    freopen("B.in", "rt", stdin);
    freopen("B.out", "wt", stdout);
    clock_t start = clock();
#endif
    solution();
#ifdef HOME
    cerr << "Total time: " << fixed << setprecision(3) << double(clock() - start) / double(CLOCKS_PER_SEC) << endl;
#endif
    return EXIT_SUCCESS;
}

typedef long long ll;
#define int ll

#define N 64
int n, m, a[N], b[N][N], b_min[N][N], b_max[N][N], p[N];

pair<int,int> f(int x, int y)
{
    pair<int,int> r(x/y, x/y);

    while (r.first > 0 && (r.first - 1) * y * 110 >= x * 100)
        --r.first;
    while (r.first * y * 110 < x * 100)
        ++r.first;

    while ((r.second + 1) * y * 90 <= x * 100)
        ++r.second;
    while (r.second * y * 90 > x * 100)
        --r.second;
    return r;
}

int solve()
{
    for (int i = 0; i < n; ++i)
        sort(b[i], b[i] + m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            auto r = f(b[i][j], a[i]);
            b_min[i][j] = r.first;
            b_max[i][j] = r.second;
        }
    int ans = 0;
    for (int i = 0; i < n; ++i)
        p[i] = 0;
    /*
    cerr << "n: " << n << " m: " << m << endl;
    for (int i = 0; i < n; ++i)
        cerr << " " << a[i];
    cerr << endl;
    cerr << "b: " << endl;
    for (int i = 0; i < n; ++i, cerr << endl)
        for (int j = 0; j < m; ++j)
            cerr << b[i][j] << " ";
    cerr << endl;
    for (int i = 0; i < n; ++i, cerr << endl)
        for (int j = 0; j < m; ++j)
            cerr << b_min[i][j] << "/" << b_max[i][j] << " ";
    cerr << endl;
    */
    for (;;)
    {
        bool fnd = false;
        for (int i = 0; i < n; ++i)
            if (p[i] >= m)
                fnd = true;
        if (fnd)
            break;
        int a_min = b_min[0][p[0]], a_max = b_max[0][p[0]];
        for (int i = 0; i < n; ++i)
        {
            a_min = max(a_min, b_min[i][p[i]]);
            a_max = min(a_max, b_max[i][p[i]]);
        }
        if (a_min <= a_max)
        {
            ++ans;
            for (int i = 0; i < n; ++i)
                ++p[i];
        }
        else
        {
            for (int i = 0; i < n; ++i)
                if (b_max[i][p[i]] < a_min)
                    ++p[i];
        }
    }
    return ans;
}

void solution()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        cerr << t + 1 << endl;
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> b[i][j];
        cout << "Case #" << t + 1 << ": " << solve() << "\n";
    }
}
