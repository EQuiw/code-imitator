#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 5;
int T, Case, n;
int a[6];
typedef pair<int, int> pii;
char color[] = "ROYGBV", s[N];

struct node {
  int cnt, id, first;
  node(int c, int i, int f = 0) : cnt(c), id(i), first(f) {}
  bool operator<(const node &rhs) const {
    if (cnt == rhs.cnt)
      return first < rhs.first;
    return cnt < rhs.cnt;
  }
};

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("out0.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    priority_queue<node> Q;
    for (int i = 0; i < 6; i++) {
      scanf("%d", &a[i]);
      if (a[i])
        Q.push(node(a[i], i));
    }
    int C = 0;
    node pre = Q.top();
    Q.pop();
    s[C++] = color[pre.id];
    pre.first = 1;
    while (Q.size()) {
      node cur = Q.top();
      Q.pop();
      s[C++] = color[cur.id];
      if (--pre.cnt > 0)
        Q.push(pre);
      pre = cur;
    }
    printf("Case #%d: ", ++Case);
    s[n] = 0;
    if (C < n || s[0] == s[n - 1])
      puts("IMPOSSIBLE");
    else
      puts(s);
  }
  return 0;
}
