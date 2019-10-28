#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int ans;
vector<int> idx;
vector<long long int> rr;
vector<vector<long long int>> ar;
int n, p;

void solve(int goal, int beg, int cur) {
  if (cur == goal) {
    int tmp = 0;
    for (int i = 0; i < p; ++i) {
      int l = int(ceil(ar[0][i] / (rr[0] * 1.1)));
      int r = int(ar[0][i] / (rr[0] * 0.9));
      if (n == 2) {
        l = max(l, int(ceil(ar[1][idx[i]] / (rr[1] * 1.1))));
        r = min(r, int(ar[1][i] / (rr[1] * 0.9)));
      }
      if (l <= r && r)
        tmp++;
    }
    ans = max(ans, tmp);
    return;
  }
  for (int i = beg; cur + p - i >= goal && i < p; ++i) {
    idx[cur] = i;
    solve(goal, i + 1, cur + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);

  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    ans = 0;
    cin >> n >> p;
    rr.resize(n);
    for (int i = 0; i < n; ++i) {
      cin >> rr[i];
    }
    ar.resize(n);
    for (int i = 0; i < n; ++i) {
      ar[i].resize(p);
      for (int j = 0; j < p; ++j) {
        cin >> ar[i][j];
      }
    }
    idx.resize(p);
    solve(p, 0, 0);

    cout << "Case #" << t << ": " << ans << endl;
  }
}