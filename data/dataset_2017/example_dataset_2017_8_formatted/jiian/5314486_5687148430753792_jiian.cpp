#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int cnt[1234], oq[1234], num[1234];
vector<int> G[1234];

struct node {
  int r, cnt;
  bool operator<(const node &a) const { return cnt > a.cnt; }
};

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  scanf("%d", &T);
  while (T--) {
    int n, c, m;
    scanf("%d %d %d", &n, &c, &m);
    memset(cnt, 0, sizeof cnt);
    memset(oq, 0, sizeof oq);
    memset(num, 0, sizeof num);
    for (int i = 1; i <= n; i++)
      G[i].clear();
    int mx = 0;
    for (int i = 0; i < m; i++) {
      int r, id;
      scanf("%d %d", &r, &id);
      G[r].push_back(id);
      mx = max(mx, ++num[id]);
    }
    int ans, pro;
    for (int w = mx; w <= m; w++) {
      int flag = 1, need = 0, r = 0;
      // priority_queue <node> q;
      for (int i = 1; i <= n; i++) {
        if (G[i].size() < w)
          r += w - G[i].size();
        else if (G[i].size() - w > r)
          flag = 0;
        else
          need += G[i].size() - w, r -= G[i].size() - w;
      }
      if (flag) {
        ans = w;
        pro = need;
        break;
      }
    }
    printf("Case #%d: %d %d\n", ++cas, ans, pro);
  }
  return 0;
}