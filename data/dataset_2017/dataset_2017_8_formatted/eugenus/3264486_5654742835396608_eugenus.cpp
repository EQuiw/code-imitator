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

#define forn(i, n) for (int i = 0; i < (n); i++)
#define forsn(i, s, n) for (int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair
#define PI acos(-1)
#define EPS 1e-8

using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  tint n, k;

  cin >> t;

  forsn(caso, 1, t + 1) {
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