#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define RI(i, n) FOR(i, 1, (n))
#define REP(i, n) FOR(i, 0, (n)-1)
#define mini(a, b) a = min(a, b)
#define maxi(a, b) a = max(a, b)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define sz(w) (int)w.size()
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 1e6 + 5;

int t, k;
string s;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  RI(x, t) {
    cin >> s >> k;
    int ans = 0;
    REP(i, sz(s) - k + 1) {
      if (s[i] == '-') {
        FOR(j, i, i + k - 1)
        if (s[j] == '+')
          s[j] = '-';
        else
          s[j] = '+';
        ans++;
      }
    }
    REP(i, sz(s)) if (s[i] == '-') {
      ans = -1;
      break;
    }
    cout << "Case #" << x << ": ";
    if (ans == -1)
      cout << "IMPOSSIBLE\n";
    else
      cout << ans << endl;
  }
  return 0;
}
