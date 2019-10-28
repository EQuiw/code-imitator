#include <vector>
#include<cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <unordered_map>
#include <cassert>
#endif
#include <ctime>
#include <queue>
#include <stack>
#include<iomanip>
#include <sstream>
#include <cmath>
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

const int N = 1000010;

void add_pll(vector<PLL>& v, const PLL p) {
    if (p.first == 0) return;
    //cout << "add_pll " << p.first << " " << p.second << endl;
    for(int i = 0; i < v.size(); i++) {
        if (v[i].first == p.first) {
            v[i].second += p.second;
            return;
        }
    }
    v.push_back(p);
}
void solve(int ncase) {
    ll n, k;
    cin >> n >> k;
    vector<PLL> v(1, PLL(n, 1));
    for(;;) {
        vector<PLL> nextv;
        for(int i = 0; i < v.size(); i++) {
            ll a = (v[i].first - 1) / 2;
            ll b = v[i].first - 1 - a;
            //cout << k << " " << v[i].first << " " << v[i].second << endl;
            if (k <= v[i].second) {
                cout << "Case #" << ncase << ": " << max(a, b) << " " << min(a, b) << endl;
                return;
            }
            add_pll(nextv, PLL(a, v[i].second));
            add_pll(nextv, PLL(b, v[i].second));
            k -= v[i].second;
        }
        v = nextv;
        sort(v.begin(), v.end(), greater<PLL>());
    }

}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    //cout << setprecision(16) << endl;
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    //precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
