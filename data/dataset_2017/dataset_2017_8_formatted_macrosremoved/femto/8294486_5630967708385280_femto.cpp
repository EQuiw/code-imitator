#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double K[1000];
double S[1000];

void solve() {
  double D;
  int N;
  cin >> D >> N;
  for (int i = 0; i < N; i++) {
    cin >> K[i] >> S[i];
  }

  double t = 0;
  for (int i = N - 1; i >= 0; i--) {
    t = max(t, (D - K[i]) / S[i]);
  }
  cout << fixed << setprecision(15) << D / t << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}
