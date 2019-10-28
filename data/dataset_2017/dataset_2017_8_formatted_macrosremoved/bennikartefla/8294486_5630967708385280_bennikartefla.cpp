#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1 << 31);
const double pi = acos(-1);

int main() {
  cin.sync_with_stdio(false);
  ofstream fout("ans2.txt");
  int t;
  cin >> t;
  for (int u = (0); u < (t); u++) {
    double n, m;
    cin >> n >> m;
    double t2 = 0;
    for (int i = (0); i < (m); i++) {
      double a, b;
      cin >> a >> b;
      double t = (n - a) / b;
      t2 = max(t, t2);
    }
    fout << "Case #" << u + 1 << ": " << setprecision(10) << fixed << n / t2
         << endl;
  }
  return 0;
}
