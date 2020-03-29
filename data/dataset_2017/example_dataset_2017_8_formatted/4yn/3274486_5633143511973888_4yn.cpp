#include <bits/stdc++.h>
using namespace std;

#define EPS 0.0000001f

typedef double dbl;
typedef pair<dbl, int> pdi;

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    int n, k;
    priority_queue<pdi> qu;
    dbl u, m[59];

    cin >> n >> k >> u;

    for (int i = 0; i < n; i++) {
      cin >> m[i];
      qu.push(pdi(1 - m[i], i));
    }

    vector<int> cu;

    cu.push_back(qu.top().second);
    qu.pop();
    // cout << "added " << cu[cu.size()-1] << " to stack\n";

    while (u > EPS) {
      // upgrade all in cu up to qu.top().first
      dbl ud;
      if (!qu.empty()) {
        ud = 1.0 - qu.top().first - m[cu[0]];
        ud = min(ud, u / cu.size());
      } else {
        ud = u / cu.size();
      }
      // cout << "pushing upgrade of size " << ud << endl;
      for (auto i : cu) {
        m[i] = min(m[i] + ud, 1.0);
        u -= ud;
      }
      cu.push_back(qu.top().second);
      qu.pop();
      // cout << "added " << cu[cu.size()-1] << " to stack\n";
    }

    dbl ans = 1;
    for (int i = 0; i < n; i++) {
      ans = ans * m[i];
    }
    cout << "Case #" << t << ": " << fixed << setprecision(7) << ans << endl;
  }
}