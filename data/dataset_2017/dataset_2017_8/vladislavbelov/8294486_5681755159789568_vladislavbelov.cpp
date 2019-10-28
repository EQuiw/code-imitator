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
    freopen("C.in", "rt", stdin);
    freopen("C.out", "wt", stdout);
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

#define N 128
#define Q 128
#define INF 1e18
#define EPS 1e-9
int n, q, e[N], s[N], g[N][N];
int from[Q], to[Q];

double dp[N];

void solve()
{
    for (int i = 0; i < n; ++i)
        dp[i] = INF;
    dp[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        double d = 0;
        for (int j = i + 1; j < n; ++j)
        {
            d += g[j-1][j];
            if (fabs(d - e[i]) < EPS || d < e[i])
            {
                dp[j] = min(dp[j], dp[i] + d / s[i]);
            }
            else
            {
                break;
            }
        }
    }
    cout << setprecision(9) << fixed << dp[n-1];
}

void solution()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        cerr << t + 1 << endl;
        cout << "Case #" << t + 1 << ": ";
        cin >> n >> q;
        for (int i = 0; i < n; ++i)
            cin >> e[i] >> s[i];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> g[i][j];
        for (int i = 0; i < q; ++i)
        {
            cin >> from[i] >> to[i];
            --from[i];
            --to[i];
        }
        solve();
        cout << '\n';
    }
}
