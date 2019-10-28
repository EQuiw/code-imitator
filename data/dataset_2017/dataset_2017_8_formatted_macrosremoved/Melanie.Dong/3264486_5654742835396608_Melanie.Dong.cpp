#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

priority_queue<LL, vector<LL>, less<LL>> q;
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.out", "w", stdout);
  int t, ca = 1;
  scanf("%d", &t);
  while (t--) {
    printf("Case #%d: ", ca++);
    LL n, k;
    cin >> n >> k;
    while (!q.empty())
      q.pop();
    q.push(n);
    LL ans1 = n, ans2 = n;
    while (k--) {
      int cur = q.top();
      q.pop();
      cur--;
      if (cur & 1)
        ans1 = cur / 2 + 1, ans2 = cur / 2;
      else
        ans1 = ans2 = cur / 2;
      q.push(ans1), q.push(ans2);
    }
    cout << ans1 << " " << ans2 << endl;
  }
  return 0;
}
