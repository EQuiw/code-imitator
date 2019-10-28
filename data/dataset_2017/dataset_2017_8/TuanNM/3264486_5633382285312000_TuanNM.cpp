#include <bits/stdc++.h>
#define TR(c, it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define FOR(i, a, b) for(int i = (a), _b = (b); i < _b; ++i)
#define FORD(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define FORE(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define SZ(c) (int) (c).size()

using namespace std;

const int N = 100010;

int a[20];
vector<long long> b;

void genX(int d, int n) {
    if (d > n) {
        long long value = 0;
        for (int i = 1; i <= n; ++i) value = value * 10 + a[i];
        b.push_back(value);
        return;
    }
    for (int c = (d > 1) ? (a[d - 1]) : 1; c <= 9; ++c) {
        a[d] = c;
        genX(d + 1, n);
    }
}
long long solve(long long value) {
    int ll = 0, rr = SZ(b) - 1;
    while (ll < rr) {
        int mm = (ll + rr + 1) >> 1;
        if (b[mm] > value) rr = mm - 1;
        else ll = mm;
    }
    return b[ll];
}
long long n;

int main() {
    //freopen("A.inp", "r", stdin);
    //freopen("A.out", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(NULL);

    a[0] = 0;
    for (int i = 1; i <= 18; ++i) {
        genX(1, i);
    }

    int nTest;
    cin >> nTest;
    for (int test = 1; test <= nTest; ++test){
        cin >> n;
        cout << "Case #" << test << ": " << solve(n) << endl;
    }

    return 0;
}

