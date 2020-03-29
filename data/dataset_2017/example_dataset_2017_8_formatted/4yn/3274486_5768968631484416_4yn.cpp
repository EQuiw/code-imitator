#include <bits/stdc++.h>
#define PI 3.141592653f
using namespace std;
typedef long long int lli;
typedef pair<lli, lli> pii;

// cout << fixed << setprecision(7) << _

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    lli n, k;
    cin >> n >> k;
    vector<pii> cakes;
    lli r, h;
    for (int i = 0; i < n; i++) {
      cin >> r >> h;
      cakes.push_back(pii(2 * r * h, r * r));
    }
    // sort(cakes.begin(),cakes.end());
    lli ans = 0;
    for (int i = 0; i < n; i++) {
      lli cur = 0;
      priority_queue<lli> ontop;
      for (int j = 0; j < n; j++) {
        if (i == j)
          continue;
        ontop.push(cakes[j].first);
      }
      for (int j = 1; j < k; j++) {
        cur += ontop.top();
        ontop.pop();
      }
      cur += cakes[i].first + cakes[i].second;
      // cout << cur << endl;
      ans = max(cur, ans);
    }
    cout << "Case #" << t << ": " << fixed << setprecision(7) << ans * PI
         << endl;
  }
}