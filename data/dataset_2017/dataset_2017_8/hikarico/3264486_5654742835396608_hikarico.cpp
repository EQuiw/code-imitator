#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct pos {
    int L, R;
    pos() {}
    pos(int L, int R): L(L), R(R) {}
    bool operator < (const pos& p) const {
        int s1 = R-L;
        int s2 = p.R-p.L;
        return s1 < s2 || (s1 == s2 && L > p.L);
    }
};

int t, n, k;
priority_queue<pos> pq;

int main() {
    int tc = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        pq = priority_queue<pos>();
        pq.push(pos(0, n-1));
        pos top;
        for (int i = 0; i < k; ++i) {
            top = pq.top();
            int L = top.L;
            int R = top.R;
            int M = (L + R) / 2;
            // choose this stall
            pq.push(pos(L, M-1));
            pq.push(pos(M+1, R));
            pq.pop();
        }
        int L = top.L;
        int R = top.R;
        int M = (L + R) / 2;
        int left = M - L;
        int right = R - M;
        int mn = min(left, right);
        int mx = max(left, right);
        printf("Case #%d: %d %d\n", ++tc, mx, mn);
    }
}
