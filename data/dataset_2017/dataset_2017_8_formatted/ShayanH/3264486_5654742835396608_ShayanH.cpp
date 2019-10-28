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

int main() {
  ios::sync_with_stdio(false);
  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "Case #" << tc << ": ";

    int n, k;
    cin >> n >> k;
    queue<int> q;
    q.push(1);
    q.push(n + 1);

    int x, y, mid;
    for (int i = 0; i < k; i++) {
      x = q.front();
      q.pop();
      y = q.front();
      q.pop();
      mid = (x + y) / 2;

      // cerr << VAL(x) << VAL(y) << VAL(mid) << endl;

      if ((y - x) % 2 == 0) {
        if (mid - x > 0) {
          q.push(x);
          q.push(mid);
        }
        if (y - mid - 1 > 0) {
          q.push(mid + 1);
          q.push(y);
        }
      } else {
        if (y - mid - 1 > 0) {
          q.push(mid + 1);
          q.push(y);
        }
        if (mid - x > 0) {
          q.push(x);
          q.push(mid);
        }
      }
    }
    cout << mid - x << ' ' << y - mid - 1 << endl;
  }
  return 0;
}
