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

string S;
int K;

void solve() {
  cin >> S >> K;
  int N = ((int)(S).size());
  int ans = 0;
  for (int i = 0; i < N - K + 1; i++) {
    if (S[i] == '-') {
      for (int j = 0; j < K; j++) {
        if (S[i + j] == '-') {
          S[i + j] = '+';
        } else {
          S[i + j] = '-';
        }
      }
      ans++;
    }
  }
  bool good = true;
  for (int i = 0; i < N; i++) {
    if (S[i] == '-')
      good = false;
  }
  if (good) {
    cout << ans << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
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
