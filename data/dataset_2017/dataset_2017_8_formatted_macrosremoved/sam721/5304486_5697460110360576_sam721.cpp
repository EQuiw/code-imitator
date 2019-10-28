#include <bits/stdc++.h>

using namespace std;
int n, R[51], Q[51][51], p, t;
int match[1010];
bool v[1010];
vector<int> g[1010];
int cap[51][51];
pair<int, int> M[51][51];
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
bool inter(pair<int, int> a, pair<int, int> b) {
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
          M[i][j] = make_pair(-0x3f3f3f3f, -0x3f3f3f3f);
        else {
          M[i][j] = make_pair(y, x);
        }
      }
    }
    for (int i = 1; i <= p; i++) {
      for (int j = 1; j <= p; j++) {
        if (M[1][i].first == -0x3f3f3f3f || M[2][j].first == -0x3f3f3f3f)
          continue;
        if (inter(M[1][i], M[2][j]))
          g[i].push_back(j + p);
      }
    }
    printf("Case #%d: %d\n", c, mf());
    for (int i = 0; i <= n * p; i++)
      g[i].clear();
  }
  return 0;
}
