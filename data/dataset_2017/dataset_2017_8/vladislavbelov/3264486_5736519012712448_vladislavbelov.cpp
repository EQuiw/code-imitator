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
    freopen("A.in", "rt", stdin);
    freopen("A.out", "wt", stdout);
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

void solution()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        string s;
        int n, k;
        cin >> s >> k;
        cerr << t + 1 << endl;
        cout << "Case #" << t + 1 << ": ";
        n = s.size();
        int ans = 0;
        for (int i = 0; i < n - k + 1; ++i)
            if (s[i] != '+')
            {
                ++ans;
                for (int j = 0; j < k; ++j)
                    if (s[i + j] == '+')
                        s[i + j] = '-';
                    else
                        s[i + j] = '+';
            }
        bool ok = true;
        for (int i = 0; i < n; ++i)
            if (s[i] != '+')
                ok = false;
        if (ok)
            cout << ans;
        else
            cout << "IMPOSSIBLE";
        cout << endl;
    }
}
