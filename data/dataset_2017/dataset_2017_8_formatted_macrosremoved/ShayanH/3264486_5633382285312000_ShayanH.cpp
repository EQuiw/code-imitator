#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;

bool is_tidy(int n) {
  vector<int> d;
  while (n) {
    int x = n % 10;
    if (((int)(d).size()) && x > d.back())
      return false;
    d.push_back(x);
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
