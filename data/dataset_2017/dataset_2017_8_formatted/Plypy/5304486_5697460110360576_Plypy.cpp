#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
int R[MAXN];
int Q[MAXN][MAXN];
int N, P;
int mi[MAXN][MAXN];
int ma[MAXN][MAXN];
bool used[MAXN][MAXN];

bool check(int n, int r, int q) {
  if (n * r * 0.9 > q)
    return false;
  if (n * r * 1.1 < q)
    return false;
  return true;
}

bool find(int l, int r, int dep) {
  if (dep == N) {
    return true;
  }
  for (int i = 0; i < P; ++i) {
    int nl = max(l, mi[dep][i]);
    int nr = min(r, ma[dep][i]);
    if (nl > nr)
      continue;
    used[dep][i] = true;
    if (find(nl, nr, dep + 1)) {
      return true;
    }
    used[dep][i] = false;
  }
  return false;
}
int solve() {
  cin >> N >> P;
  for (int i = 0; i < N; ++i)
    cin >> R[i];

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < P; ++j) {
      cin >> Q[i][j];

      mi[i][j] = ceil(Q[i][j] / (1.1 * R[i]));
      ma[i][j] = Q[i][j] / (0.9 * R[i]);
    }

  memset(used, 0, sizeof(used));
  int ret = 0;
  for (int i = 0; i < P; ++i) {
    if (mi[0][i] > ma[0][i])
      continue;
    if (find(mi[0][i], ma[0][i], 1)) {
      ++ret;
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    printf("Case #%d: %d\n", cas, solve());
  }
}
