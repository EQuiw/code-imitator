/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main() {
  ios::sync_with_stdio(false);

  solution();

  return EXIT_SUCCESS;
}

typedef long long ll;

void solution() {
  ll T;
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    string s;
    ll n, k;
    cin >> s >> k;
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ": ";
    n = s.size();
    ll ans = 0;
    for (ll i = 0; i < n - k + 1; ++i)
      if (s[i] != '+') {
        ++ans;
        for (ll j = 0; j < k; ++j)
          if (s[i + j] == '+')
            s[i + j] = '-';
          else
            s[i + j] = '+';
      }
    bool ok = true;
    for (ll i = 0; i < n; ++i)
      if (s[i] != '+')
        ok = false;
    if (ok)
      cout << ans;
    else
      cout << "IMPOSSIBLE";
    cout << endl;
  }
}
