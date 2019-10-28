#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 1e6 + 5;

int t;
string s;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int x = (1); x <= ((t)); ++x) {
    cin >> s;
    for (int i = ((int)s.size() - 2); i >= (0); --i) {
      if (s[i + 1] < s[i]) {
        for (int j = (i + 1); j <= ((int)s.size() - 1); ++j)
          s[j] = '9';
        s[i]--;
      }
    }
    if (s[0] == '0')
      s = s.substr(1, (int)s.size() - 1);
    cout << "Case #" << x << ": ";
    cout << s << endl;
  }
  return 0;
}
