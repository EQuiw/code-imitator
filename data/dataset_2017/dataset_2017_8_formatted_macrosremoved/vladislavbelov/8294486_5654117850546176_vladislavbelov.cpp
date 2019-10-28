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

ll n;
pair<ll, ll> c[6], t[6];
string alpha = "ROYGBV";

bool is_good(const string &s) {
  for (ll i = 1; i < (ll)s.size(); ++i)
    if (s[i] == s[i - 1])
      return false;
  if (s[0] == s.back())
    return false;
  return true;
}

ll all_imp = 0;

void solve() {
  sort(c, c + 6);
  reverse(c, c + 6);
  if (c[1].first == 0) {
    ++all_imp;
    cout << "IMPOSSIBLE";
  } else if (c[2].first == 0) {
    if (n % 2 == 0) {
      if (c[0].first == c[1].first) {
        for (ll i = 0; i < n; ++i)
          cout << alpha[c[i % 2].second];
      } else {
        ++all_imp;
        cout << "IMPOSSIBLE";
      }
    } else {
      ++all_imp;
      cout << "IMPOSSIBLE";
    }
  } else if (c[3].first == 0) {
    if (c[0].first > c[1].first + c[2].first) {
      ++all_imp;
      cout << "IMPOSSIBLE";
      return;
    }
    string s;
    s += alpha[c[0].second];
    --c[0].first;
    for (ll i = 1; i < n; ++i) {
      sort(c, c + 6);
      reverse(c, c + 6);
      for (ll j = 0; j < 3; ++j)
        if (alpha[c[j].second] != s[i - 1] && c[j].first > 0) {
          s += alpha[c[j].second];
          --c[j].first;
          break;
        }
    }
    if (is_good(s))
      cout << s;
    else {
      do {
        if (is_good(s)) {
          cout << s;
          return;
        }
      } while (next_permutation(s.begin() + max(0ll, n - 10), s.end()));
      cout << "IMPOSSIBLE";
      ++all_imp;
    }
  } else {
    cout << "!fail!";
  }
}

void solution() {
  ll T;
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ": ";
    cin >> n;
    for (ll i = 0; i < 6; ++i) {
      cin >> c[i].first;
      c[i].second = i;
    }
    solve();
    cout << '\n';
  }
  cerr << "a: " << all_imp << endl;
}
