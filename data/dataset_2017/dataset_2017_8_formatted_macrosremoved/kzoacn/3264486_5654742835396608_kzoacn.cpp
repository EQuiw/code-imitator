#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct sta {
  int l, r;
  int len() const { return r - l + 1; }

  bool operator<(const sta &oth) const {
    return len() != oth.len() ? len() < oth.len() : l > oth.l;
  }
};
void solve() {
  int n, k;
  cin >> n >> k;
  priority_queue<sta> q;
  q.push((sta){1, n});
  int ans1, ans2;
  while (k--) {
    sta u = q.top();
    q.pop();
    int l = u.l, r = u.r;
    int m = (l + r) >> 1;
    //		cerr<<l<<" "<<r<<" "<<m<<endl;
    ans1 = max(m - l, r - m);
    ans2 = min(m - l, r - m);
    if (l <= m - 1)
      q.push((sta){l, m - 1});
    if (m + 1 <= r)
      q.push((sta){m + 1, r});
  }
  printf("%d %d\n", ans1, ans2);
}
int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    printf("Case #%d: ", t);
    solve();
  }
  return 0;
}
