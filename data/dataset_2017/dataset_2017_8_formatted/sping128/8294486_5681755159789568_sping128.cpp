#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)(x).size())
#define PB(x) push_back(x)
#define MEMSET(x, v) memset(x, v, sizeof(x))
#define REP(i, n) for (int(i) = 0; (i) < (n); ++(i))
#define x first
#define y second
#define INF (0x3f3f3f3f)

typedef long long LL;
typedef pair<int, int> P2;
template <class A, class B> inline bool mina(A &x, B y) {
  return (x > y) ? (x = y, 1) : 0;
}
template <class A, class B> inline bool maxa(A &x, B y) {
  return (x < y) ? (x = y, 1) : 0;
}

const int MAXN = 105;

int N, Q;
int E[MAXN], S[MAXN];
LL dist[MAXN][MAXN];

double min_cost[MAXN];

P2 queries[MAXN];

void solve() {
  cin >> N >> Q;
  REP(i, N) {
    cin >> E[i] >> S[i];
    min_cost[i] = 1e15;
  }
  REP(i, N) {
    REP(j, N) {
      cin >> dist[i][j];
      if (dist[i][j] == -1) {
        dist[i][j] = INF;
      }
    }
  }
  REP(i, Q) {
    cin >> queries[i].x >> queries[i].y;
    queries[i].x--;
    queries[i].y--;
  }
  REP(k, N) {
    REP(i, N) {
      REP(j, N) { mina(dist[i][j], dist[i][k] + dist[k][j]); }
    }
  }
  min_cost[0] = 0.0;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i; j++) {
      if (dist[j][i] <= E[j]) {
        double nx = min_cost[j] + dist[j][i] * 1.0 / S[j];
        mina(min_cost[i], nx);
      }
    }
  }
  //  cout << queries[0].y << endl;
  REP(i, Q) { printf(" %.9lf", min_cost[queries[i].y]); }
  cout << endl;
}

int main() {
  int test;
  cin >> test;
  REP(tt, test) {
    cout << "Case #" << (tt + 1) << ":";
    solve();
  }

  return 0;
}
