#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1010;
class CNode {
public:
  int len, l, r;
  CNode() {}
  CNode(int _len, int _l, int _r) : len(_len), l(_l), r(_r) {}
  bool operator<(const CNode &b) const {
    if (len != b.len)
      return len < b.len;
    else
      return l > b.l;
  }
  bool operator>(const CNode &b) const { return !((*this) < b); }
};
int n, k;
bool vis[maxn];
priority_queue<CNode> PriorityQ;
inline void solve() {
  memset(vis, false, sizeof(vis));
  while (!PriorityQ.empty())
    PriorityQ.pop();
  scanf("%d%d", &n, &k);
  int mid;
  CNode cur, left, right;
  PriorityQ.push(CNode(n, 0, n - 1));
  for (int i = 0; i < k; i++) {
    cur = PriorityQ.top();
    PriorityQ.pop();
    mid = (cur.l + cur.r) >> 1;
    vis[mid] = true;
    if (cur.len == 1)
      continue;
    right.l = mid + 1;
    right.r = cur.r;
    right.len = right.r - right.l + 1;
    left.l = cur.l;
    left.r = mid - 1;
    left.len = left.r - left.l + 1;
    if (left.l <= left.r)
      PriorityQ.push(left);
    if (right.l <= right.r)
      PriorityQ.push(right);
  }
  int i, cntl = 0, cntr = 0;
  i = mid;
  while (--i >= 0 && !vis[i])
    cntl++;
  i = mid;
  while (++i < n && !vis[i])
    cntr++;
  printf("%d %d\n", max(cntl, cntr), min(cntl, cntr));
}
int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int tcase = 1; tcase <= T; tcase++) {
    printf("Case #%d: ", tcase);
    solve();
  }
  return 0;
}