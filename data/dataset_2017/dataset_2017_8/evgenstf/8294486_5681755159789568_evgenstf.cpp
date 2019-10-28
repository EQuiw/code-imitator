#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <cassert>

using namespace std;

typedef long long ll;
typedef long double ld;

const long double inf = 1e18 + 7;

const long double eps = 1e-8;

int main() {
ios_base::sync_with_stdio(0);
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    for (int tt = 0; tt < t; ++tt) {
        int n, q;
        cin >> n >> q;
        vector<pair<int, ll> > hourses;
        for (int i = 0; i < n; ++i) {
            int s;
            ll v;
            cin >> s >> v;
            hourses.push_back({s, v});
        }

        vector<ll> roads;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int x;
                cin >> x;
                if (x != -1)
                    roads.push_back(x);
            }

        int a, b;
        cin >> a >> b;
        vector<long double> dp(n, inf);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            ll snow = 0;
            int j = 1;
            while (i + j < n && snow <= hourses[i].first){
                snow += roads[i + j - 1];
                if (!(snow <= hourses[i].first))
                    break;
                dp[i + j] = min(dp[i + j], dp[i] + ((long double)snow) / hourses[i].second);
                j ++;
            }
        }
        cout << "Case #" << tt + 1 << ": ";
        cout.precision(10);
        cout << fixed << dp[n - 1] << "\n";
    }
    return 0;
}
