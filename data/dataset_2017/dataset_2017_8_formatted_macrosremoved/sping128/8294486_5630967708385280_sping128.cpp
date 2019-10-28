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

const int MAXN = 1005;

int D, N;
int K[MAXN];
int S[MAXN];

void solve() {
  cin >> D >> N;
  for (int(i) = 0; (i) < (N); ++(i)) {
    cin >> K[i] >> S[i];
  }
  double tt = (D - K[0]) * 1.0 / S[0];
  for (int(i) = 0; (i) < (N); ++(i)) {
    maxa(tt, (D - K[i]) * 1.0 / S[i]);
  }
  printf("%.9lf\n", D / tt);
}

int main() {
  int test;
  cin >> test;
  for (int(tt) = 0; (tt) < (test); ++(tt)) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}
