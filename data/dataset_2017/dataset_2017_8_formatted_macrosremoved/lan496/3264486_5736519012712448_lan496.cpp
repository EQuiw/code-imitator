#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

int solve(const string &S, int K) {
  int N = S.length();
  vector<int> a(N);
  for (int i = 0; i < (int)(N); i++) {
    if (S[i] == '+')
      a[i] = 0;
    else
      a[i] = 1;
  }
  int res = 0;
  for (int i = 0; i < (int)(N - K + 1); i++) {
    if (a[i] % 2) {
      ++res;
      for (int j = 0; j < (int)(K); j++)
        ++a[i + j];
    }
  }
  for (int i = N - K + 1; i < N; ++i) {
    if (a[i] % 2)
      return -1;
  }
  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < (int)(T); t++) {
    string S;
    int K;
    cin >> S >> K;
    int res = solve(S, K);
    cout << "Case #" << t + 1 << ": "
         << (res == -1 ? "IMPOSSIBLE" : to_string(res)) << endl;
  }
  return 0;
}
