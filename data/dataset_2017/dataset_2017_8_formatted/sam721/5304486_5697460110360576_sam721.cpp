#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define VI vector<int>
#define LL long long
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
using namespace std;
int n, R[51], Q[51][51], p, t;
int match[1010];
bool v[1010];
VI g[1010];
int cap[51][51];
pii M[51][51];
bool matching(int cur) {
  if (cur == -1)
    return true;
  v[cur] = true;
  for (int i = 0; i < (int)g[cur].size(); i++) {
    int next = g[cur][i];
    if (v[next])
      continue;
    v[next] = true;
    if (matching(match[next])) {
      match[next] = cur;
      return true;
    }
  }
  return false;
}
int mf() {
  memset(match, -1, sizeof(match));
  int flow = 0;
  for (int i = 1; i <= p; i++) {
    memset(v, false, sizeof(v));
    flow += matching(i);
  }
  return flow;
}
bool inter(pii a, pii b) {
  int li = a.first, ls = a.second, i = b.first, j = b.second;
  return !(i > ls || j < li);
}
int main() {
  scanf("%d", &t);
  for (int c = 1; c <= t; c++) {
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++)
      scanf("%d", &R[i]);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= p; j++) {
        scanf("%d", &Q[i][j]);
        int l = 90 * R[i] / 100 + (bool)((90 * R[i]) % 100);
        int r = (110 * R[i]) / 100;
        int x = Q[i][j] / l, y = (Q[i][j] / r) + (bool)(Q[i][j] % r);
        if (x < y)
          M[i][j] = mp(-INF, -INF);
        else {
          M[i][j] = mp(y, x);
        }
      }
    }
    for (int i = 1; i <= p; i++) {
      for (int j = 1; j <= p; j++) {
        if (M[1][i].first == -INF || M[2][j].first == -INF)
          continue;
        if (inter(M[1][i], M[2][j]))
          g[i].pb(j + p);
      }
    }
    printf("Case #%d: %d\n", c, mf());
    for (int i = 0; i <= n * p; i++)
      g[i].clear();
  }
  return 0;
}