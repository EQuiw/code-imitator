#include <vector>
#include <cstdio>
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
//#include "utils/haha.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

const string noway = "IMPOSSIBLE";

int n, r, o, y, g, b, v;

int memo[3][1024][1024][1024];

void precalc() {CLS(memo, -1);}


bool dfs(int pre, int nr, int ny, int nb, int idx, vector<int>& s) {
    if (nr < 0 || ny < 0 || nb < 0) return false;
    //fprintf(stderr, "pre %d, nr %d, ny %d, nb %d, idx %d\n", pre, nr, ny, nb, idx);
    int &tmp = memo[pre][nr][ny][nb];
    if (memo[pre][nr][ny][nb] == -2) return false;
    if (tmp != -1) {
        int p = tmp;
        for(;idx < n; idx++) {
            s[idx] = p;
            if (0 == p) nr--;
            if (1 == p) ny--;
            if (2 == p) nb--;
            p = memo[p][nr][ny][nb];
        }
        //dfs(tmp, nr, ny, nb, idx + 1, s);

        return true;
    }
    if (nr + ny + nb == 0) {
        if (pre == 0) tmp = -2;
        else tmp = pre;
        return tmp >= 0;
    }
    for(int p = 0; p < 3; p++) {
        if (p != pre) {
            int zr = nr;
            int zy = ny;
            int zb = nb;
            if (p == 0) zr--;
            if (p == 1) zy--;
            if (p == 2) zb--;
            if (dfs(p, zr, zy, zb, idx + 1, s)) {
                tmp = p;
                s[idx] = tmp;
                return true;
            }
        }
    }
    tmp = -2;
    return false;
}
void solve_ryb() {
    string cc = "RYB";
    vector<int> s(n, -1);
    vector<PII> color = {PII(r, 0), PII(y, 1), PII(b, 2)};
    sort(color.begin(), color.end());
    if (color[0].first == 0) {
        if (color[1].first != color[2].first) {
            cout << noway << endl;
            return;
        }
        for(int i = 0; i < n; i += 2) s[i] = color[1].second;
        for(int i = 1; i < n; i += 2) s[i] = color[2].second;
        for(auto c : s) cout << cc[c]; cout << endl;
        return;
    }
    s[0] = 0;
    if (dfs(0, r - 1, y, b, 1, s)) {
        for(auto c : s) cout << cc[c]; cout << endl;
    } else {
        cout << noway << endl;
    }
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n;
    cin >> r >> o >> y >> g >> b >> v;
    solve_ryb();
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    precalc();
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
