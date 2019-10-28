#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  tint n, k;

  cin >> t;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> n >> k;
    tint b = 62;
    while (k < (1ll << b))
      b--;
    // cout << k << " "  << b << " " << (1ll << b) << endl;
    tint nn = n + 1 - (1ll << b);
    tint q = nn / (1ll << b);
    tint r = nn % (1ll << b);
    // cout << nn << " "  << q << " " << r << endl;

    tint kk = k + 1 - (1ll << b);
    tint ma, mi;
    if (kk <= r)
      q++;
    q--;
    ma = (q + 1ll) / 2ll;
    mi = q / 2ll;

    cout << "Case #" << caso << ": " << ma << " " << mi << endl;
  }

  return 0;
}
