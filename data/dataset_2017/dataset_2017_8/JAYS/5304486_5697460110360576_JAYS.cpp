#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N, P;
ll R[11], Q[11][11];

pair<ll,ll> find(ll gram, int idx) {
    ll a = (100*gram) / (R[idx]*110);
    ll q = (100*gram) % (R[idx]*110);
    ll b = (100*gram) / (R[idx]*90);
    if (q) a++;
    return {a, b};
}

int dp[11][333];
int rec(int n, int m) {
    int& ret = dp[n][m];
    if (ret != -1) return ret;
    if (n == P) return ret = 0;
    ret = 0;
    ret = max(ret, rec(n+1, m));
    for (int i = 0; i < P; i++) {
        if (m & (1<<i)) continue;
        pair<ll,ll> cand1 = find(Q[0][n], 0);
        pair<ll,ll> cand2 = find(Q[1][i], 1);
        if (cand1.second >= cand1.first && cand2.second >= cand2.first) {
            bool found = false;
            if (cand1.first <= cand2.first && cand2.first <= cand1.second) found = true;
            if (cand1.first <= cand2.second && cand2.second <= cand1.second) found = true;
            if (found) ret = max(ret, 1+rec(n+1, m|(1<<i)));
        }
    }
    return ret;
}

int solve() {
    if (N == 1) {
        int ret = 0;
        for (int i = 0; i < P; i++) {
            pair<ll,ll> cand = find(Q[0][i], 0);
            if (cand.second-cand.first+1 >= 1) ret++;
        }
        return ret;
    } else {
        memset(dp, -1, sizeof(dp));
        return rec(0, 0);
    }
}

int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &N, &P);
        for (int i = 0; i < N; i++) scanf("%lld", R+i);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) scanf("%lld", &Q[i][j]);
        }
        int ans = solve();
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}