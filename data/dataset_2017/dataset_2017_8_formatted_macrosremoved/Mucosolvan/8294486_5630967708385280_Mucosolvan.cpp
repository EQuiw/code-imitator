#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 1e6 + 5;

int d, n, start[maxN], speed[maxN], t;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int x = (1); x <= ((t)); ++x) {
    cin >> d >> n;
    long double maxim = 0;
    for (int i = (0); i <= ((n)-1); ++i) {
      cin >> start[i] >> speed[i];
      long double time = (long double)(d - start[i]) / (long double)speed[i];
      maxim = max(maxim, time);
    }

    cout << "Case #" << x << ": ";
    cout << fixed << setprecision(12) << d / maxim << endl;
  }
  return 0;
}
