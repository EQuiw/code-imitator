#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pt;
const int base = 1000000007;
const int maxn = 1000002;

struct pt3 {
  int l, first, r;
  int Ls, Rs;
  pt3(){};
  pt3(int a, int b, int c) {
    l = a;
    first = b;
    r = c;
    Ls = first - l - 1;
    Rs = r - first - 1;
  }

  bool operator>(const pt3 &b) const {
    return (min(Ls, Rs) > min(b.Ls, b.Rs)) ||
           (min(Ls, Rs) == min(b.Ls, b.Rs) && max(Ls, Rs) > max(b.Ls, b.Rs));
  }

  bool operator<(const pt3 &b) const {
    return (min(Ls, Rs) < min(b.Ls, b.Rs)) ||
           (min(Ls, Rs) == min(b.Ls, b.Rs) && max(Ls, Rs) < max(b.Ls, b.Rs));
  }
};

int n, K, res1, res2;
int kt[maxn];
priority_queue<pt3> q;

void solve2(int test) {
  int i, j, k;
  pt3 p;

  cin >> n >> K;

  while (!q.empty())
    q.pop();
  q.push(pt3(1, (n + 3) / 2, n + 2));

  for (i = 1; i <= K; i++) {
    p = q.top();
    q.pop();
    if (kt[p.first] == test)
      continue;

    kt[p.first]++;
    res1 = max(p.Ls, p.Rs);
    res2 = min(p.Ls, p.Rs);
    q.push(pt3(p.l, (p.l + p.first) / 2, p.first));
    q.push(pt3(p.first, (p.first + p.r) / 2, p.r));
  }

  printf("Case #%d: %d %d\n", test, res1, res2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int i, t;
  freopen("cjc.in", "r", stdin);
  freopen("outputc.out", "w", stdout);

  cin >> t;
  for (i = 1; i <= t; i++)
    solve2(i);

  return 0;
}
