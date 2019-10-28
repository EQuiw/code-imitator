#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

ld solve(int D, const vector<int> &K, const vector<int> &S) {
  int N = K.size();
  vector<ld> t(N);
  for (int i = 0; i < (int)(N); i++)
    t[i] = (ld)(D - K[i]) / S[i];
  sort(t.rbegin(), t.rend());
  ld res = D / t[0];
  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < (int)(T); t++) {
    int D, N;
    cin >> D >> N;
    vector<int> K(N), S(N);
    for (int i = 0; i < (int)(N); i++)
      cin >> K[i] >> S[i];
    ld res = solve(D, K, S);
    cout << "Case #" << fixed << setprecision(10) << t + 1 << ": " << res
         << endl;
  }
  return 0;
}
