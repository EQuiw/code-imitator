#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pii = pair<int, int>;

int T, cas;

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  cin >> T;
  while (T--) {
    vector<vector<pii>> v;
    vector<int> R;
    int n, p;
    cin >> n >> p;
    for (int i = 0, x; i < n; i++)
      cin >> x, R.push_back(x);
    int mx = p;
    for (int i = 0; i < n; i++) {
      v.push_back(vector<pii>());
      for (int j = 0, x; j < p; j++) {
        cin >> x;
        int a = ceil(1 / 1.1 * x / R[i]), b = floor(1 / 0.9 * x / R[i]);
        // while (1.0 * a * R[i] < 0.9 * x) a ++;
        // while (1.0 * b * R[i] > 1.1 * x) b --;
        // cout << a << " " << b << endl;
        if (a <= b)
          v.back().emplace_back(a, b);
      }
      sort(v[i].begin(), v[i].end());
    }
    int ans = 0;
    while (true) {
      int mnv = 0, mxv = 1e9, mnid, mxid, flag = 0;
      for (int i = 0; i < n; i++)
        if (v[i].size()) {
          auto x = v[i].back();
          if (x.first > mnv)
            mnv = x.first, mnid = i;
          if (x.second < mxv)
            mxv = x.second, mxid = i;
        } else
          flag = 1;
      if (flag)
        break;
      // cout << mnv << " " << mxv << endl;
      if (mnv <= mxv) {
        ans++;
        for (int i = 0; i < n; i++)
          v[i].pop_back();
      } else {
        v[mnid].pop_back();
      }
    }
    printf("Case #%d: %d\n", ++cas, ans);
  }
  return 0;
}
