#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> P2;
template <class A, class B> inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B> inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
}

const int MAXN = 105;

int N, Q;
int E[MAXN], S[MAXN];
LL dist[MAXN][MAXN];

double min_cost[MAXN];

P2 queries[MAXN];

void solve() {
  cin >> N >> Q;
  for (int(i) = 0; (i) < (N); ++(i)) {
    cin >> E[i] >> S[i];
    min_cost[i] = 1e15;
  }
  for (int(i) = 0; (i) < (N); ++(i)) {
    for (int(j) = 0; (j) < (N); ++(j)) {
      cin >> dist[i][j];
      if (dist[i][j] == -1) {
        dist[i][j] = (0x3f3f3f3f);
      }
    }
  }
  for (int(i) = 0; (i) < (Q); ++(i)) {
    cin >> queries[i].first >> queries[i].second;
    queries[i].first--;
    queries[i].second--;
  }
  for (int(k) = 0; (k) < (N); ++(k)) {
    for (int(i) = 0; (i) < (N); ++(i)) {
      for (int(j) = 0; (j) < (N); ++(j)) {
        mina(dist[i][j], dist[i][k] + dist[k][j]);
      }
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
  for (int(i) = 0; (i) < (Q); ++(i)) {
    printf(" %.9lf", min_cost[queries[i].second]);
  }
  cout << endl;
}

int main() {
  int test;
  cin >> test;
  for (int(tt) = 0; (tt) < (test); ++(tt)) {
    cout << "Case #" << (tt + 1) << ":";
    solve();
  }

  return 0;
}
