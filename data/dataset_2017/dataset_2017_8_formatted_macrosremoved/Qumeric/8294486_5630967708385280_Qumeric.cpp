#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll t;
ll d, n;

void solve() {
  cin >> d >> n;
  vector<pair<double, double>> horses;
  double tme = -1e9;
  for (int i = 0; i < n; i++) {
    double k, s;
    cin >> k >> s;
    double ctme = (d - k) / s;
    tme = max(ctme, tme);
  }
  cout << fixed << double(d) / tme << endl;
}

int main() {
  ios::sync_with_stdio(0);
  cout.precision(10);
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
