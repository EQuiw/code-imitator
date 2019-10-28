#include <bits/stdc++.h>
using namespace std;
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
