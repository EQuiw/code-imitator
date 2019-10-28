#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  int t;
  cin >> t;
  for (int T = 1; T < t + 1; T++) {
    double mxs = 0;
    double dist;
    int n;
    cin >> dist >> n;
    for (int i = 0; i < n; i++) {
      double stt, spd;
      cin >> stt >> spd;
      mxs = max(mxs, (dist - stt) / spd);
    }
    cout.precision(6);
    cout << "Case #" << T << ": " << fixed << dist / mxs << endl;
  }
}
