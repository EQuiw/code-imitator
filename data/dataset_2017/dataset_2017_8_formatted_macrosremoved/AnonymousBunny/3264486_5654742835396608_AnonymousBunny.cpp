#include <bits/stdc++.h>
using namespace std;

set<pair<int, pair<int, int>>> s;

pair<int, pair<int, int>> get(int l, int r) {
  return make_pair(l - r, make_pair(l, r));
}

void solve(int id) {
  int n, k;
  cin >> n >> k;
  s.clear();
  s.insert(get(1, n));
  while (!s.empty()) {
    k--;
    pair<int, pair<int, int>> cur = *s.begin();
    s.erase(s.begin());
    int l = cur.second.first, r = cur.second.second;
    int mid = (l + r) / 2;
    int ld = mid - l, rd = r - mid;
    if (k == 0) {
      cout << "Case #" << id << ": " << max(ld, rd) << " " << min(ld, rd)
           << endl;
      return;
    }
    if (mid - 1 >= l)
      s.insert(get(l, mid - 1));
    if (mid + 1 <= r)
      s.insert(get(mid + 1, r));
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
}
