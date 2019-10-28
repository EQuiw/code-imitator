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

const int MAXN = 1005;

int D, N;
int K[MAXN];
int S[MAXN];

void solve() {
  cin >> D >> N;
  REP(i, N) { cin >> K[i] >> S[i]; }
  double tt = (D - K[0]) * 1.0 / S[0];
  REP(i, N) { maxa(tt, (D - K[i]) * 1.0 / S[i]); }
  printf("%.9lf\n", D / tt);
}

int main() {
  int test;
  cin >> test;
  REP(tt, test) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
