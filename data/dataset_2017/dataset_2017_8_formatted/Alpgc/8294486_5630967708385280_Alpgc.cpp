#include <bits/stdc++.h>
#define fr(a, b, c) for (int a = b; a < c; a++)
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long ll;

int main() {
  int t;
  cin >> t;
  fr(T, 1, t + 1) {
    double mxs = 0;
    double dist;
    int n;
    cin >> dist >> n;
    fr(i, 0, n) {
      double stt, spd;
      cin >> stt >> spd;
      mxs = max(mxs, (dist - stt) / spd);
    }
    cout.precision(6);
    cout << "Case #" << T << ": " << fixed << dist / mxs << endl;
  }
}
