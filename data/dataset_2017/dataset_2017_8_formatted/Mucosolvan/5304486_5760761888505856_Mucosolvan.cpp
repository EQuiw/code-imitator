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
const int maxN = 100 + 5;

int t, k, n;
int can[maxN][maxN];
string s[maxN];

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  RI(x, t) {
    cin >> n >> k;
    REP(i, n)
    cin >> s[i];

    int pom = -1;
    REP(i, n) {
      REP(j, k) {
        if (s[i][j] != '?' && (pom == i || pom == -1)) {
          REP(l, n) {
            REP(m, k) {
              if (s[l][m] == '?' && l <= i && m <= j) {
                s[l][m] = s[i][j];
              }
            }
          }
          pom = i;
        }
        // cout<<i<<" "<<j<<" "<<pom<<" "<<s[i][j]<<endl;
        if (pom != -1 && i > pom)
          break;
      }
      if (pom != -1 && i > pom)
        break;
    }

    REP(i, n) {
      int pos = -1;
      REP(j, k) {
        if (s[i][j] != '?') {
          pos = j;
          break;
        }
      }

      if (pos != -1) {
        char first = s[i][pos];
        REP(j, k) {
          if (s[i][j] == '?') {
            s[i][j] = first;
          } else {
            first = s[i][j];
          }
        }
      } else {
        REP(j, k)
        s[i][j] = s[i - 1][j];
      }
    }

    cout << "Case #" << x << ": " << endl;
    REP(i, n) { cout << s[i] << endl; }
  }
  return 0;
}
