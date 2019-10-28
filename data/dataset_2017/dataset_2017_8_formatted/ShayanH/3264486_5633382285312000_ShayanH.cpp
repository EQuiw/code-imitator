#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define SQR(a) ((a) * (a))
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define CLR(x, a) memset(x, a, sizeof x)
#define VAL(x) #x << " = " << (x) << "   "
#define FOREACH(i, x)                                                          \
  for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
#define FOR(i, n) for (int i = 0; i < (n); i++)
#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;

bool is_tidy(int n) {
  vector<int> d;
  while (n) {
    int x = n % 10;
    if (SZ(d) && x > d.back())
      return false;
    d.pb(x);
    n /= 10;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);

  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "Case #" << tc << ": ";
    int n;
    cin >> n;
    do {
      if (is_tidy(n)) {
        cout << n << endl;
        break;
      }
    } while (n--);
  }
  return 0;
}
