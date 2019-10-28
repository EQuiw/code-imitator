#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> Matrix;

const int INF = 1e9 + 7;
const double PI = acos(-1);
const double EPS = 1e-9;

const int N = 1e6 + 5;

int main() {
  int t, k;
  string s;
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cout << "Case #" << caseNr << ": ";
    cin >> s >> k;
    int res = 0;
    for (int i = (0); i < (s.size()); ++i) {
      if (s[i] == '-') {
        ++res;
        if (i + k - 1 >= s.size()) {
          cout << "IMPOSSIBLE" << endl;
          goto next;
        }
        for (int j = (0); j < (k); ++j)
          s[i + j] = s[i + j] == '+' ? '-' : '+';
      }
    }
    cout << res << endl;
  next:;
  }
  return 0;
}
