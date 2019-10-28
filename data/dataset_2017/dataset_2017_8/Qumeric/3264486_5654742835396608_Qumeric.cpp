#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll t, n, k;

pair<int, int> go(vector<int>& v) {
    vector<int> ls(v.size()), rs(v.size());
    for (int i = 0; i < n; i++) {
        if (v[i] != 0) {
            ls[i] = rs[i] = -1;
            continue;
        }
        for (int j = i-1; j >= 0; j--) {
            if (v[j] != 0)
                break;
            ls[i]++;
        }

        for (int j = i+1; j < n; j++) {
            if (v[j] != 0)
                break;
            rs[i]++;
        }
    }
    int mpos = -1, maxmin = -1e9, maxmax = -1e9;
    for (int i = 0; i < n; i++) {
        if (v[i] != 0)
            continue;
        int curmin =  min(ls[i], rs[i]);
        int curmax =  max(ls[i], rs[i]);
        if (mpos == -1 || curmin > maxmin ||
                (curmin == maxmin && curmax > maxmax)) {
            mpos = i;
            maxmin = curmin;
            maxmax = curmax;
        }
    }

    v[mpos] = 1;

    return {maxmax, maxmin};

}

void solve() {
    cin >> n >> k;

    vector<int> v(n);

    pair<int, int> p;

    for (int i = 0; i < k; i++)
        p = go(v);

    cout << p.first << ' ' << p.second << '\n';
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
