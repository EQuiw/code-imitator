#include <bits/stdc++.h>
#define ff first
#define ss second
#define ALL(x) (x).begin(), (x).end()
#define D(x) cout << ">> " << #x << " = >" << x << "<" << endl
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define PB push_back
#define R1(a) scanf("%d", &a)
#define R2(a, b) scanf("%d%d", &a, &b)
#define R3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define P(cond)                                                                \
  do {                                                                         \
    if (!(cond)) {                                                             \
      puts("Nespravny vstup.");                                                \
      return 1;                                                                \
    }                                                                          \
  } while (0)
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

  FOR(caseNr, 1, t + 1) {
    cout << "Case #" << caseNr << ": ";
    cin >> s >> k;
    int res = 0;
    FOR(i, 0, s.size()) {
      if (s[i] == '-') {
        ++res;
        if (i + k - 1 >= s.size()) {
          cout << "IMPOSSIBLE" << endl;
          goto next;
        }
        FOR(j, 0, k)
        s[i + j] = s[i + j] == '+' ? '-' : '+';
      }
    }
    cout << res << endl;
  next:;
  }
  return 0;
}
