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

bool can_server(vector<vector<int>>& g, int x, vector<int>& idx, vector<int>& r) {
    if (x == 0) return false;
    for(int i = 1; i < g.size(); i++) {
        while(idx[i] < g[0].size() && g[i][idx[i]] < 0.9 * r[i] * x) idx[i]++;
        if (idx[i] < g[0].size() && 0.9 * r[i] * x <= g[i][idx[i]] && g[i][idx[i]] <= 1.1 * r[i] * x) continue;
        return false;
    }
    return true;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n, p;
    cin >> n >> p;
    vector<int> r(n);
    for(int i = 0; i < n; i++) cin >> r[i];
    vector<vector<int>> g(n, vector<int>(p));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            cin >> g[i][j];
        }
        sort(g[i].begin(), g[i].end());
    }
    vector<int> idx(n);
    int ret = 0;
    for(int i = 0; i < p; i++) {
        int ix = g[0][i] / 1.1 / r[0]; 
        int inx = g[0][i] / 0.9 / r[0] + 1;
        while(0.9 *r[0]* ix <= g[0][i] && g[0][i] <= ix *r[0]* 1.1) ix --;
        while(0.9 *r[0]* inx <= g[0][i] && g[0][i] <= inx *r[0]* 1.1) inx ++;
        if (i + 1 < p) {
            int nix = g[0][i+1] / 1.1 / r[0];
            inx = min(inx, nix);
        }
        //cout << ix << ' ' << inx << endl;
        for(int a = ix; a <= inx; a++) {
            vector<int> nidx = idx;
            if (!(0.9 *r[0]* a <= g[0][i] && g[0][i] <= a *r[0]* 1.1)) continue;
            if (can_server(g, a, nidx, r)) {
                ret ++;
                idx = nidx;
                break;
            }
        
        }
    }
    cout << ret << endl;
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
