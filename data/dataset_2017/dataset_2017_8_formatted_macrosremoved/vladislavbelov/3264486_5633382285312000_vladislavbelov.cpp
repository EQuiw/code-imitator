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

bool is_valid(const string &s) {
  for (size_t i = 1; i < s.size(); ++i)
    if (s[i] < s[i - 1])
      return false;
  return true;
}

string solve(string s) {
  if (is_valid(s))
    return s;
  ll n = s.size();
  for (ll i = n - 1; i > 0; --i) {
    if (s[i] < s[i - 1]) {
      s[i - 1] -= 1;
      for (ll j = i; j < n; ++j)
        s[j] = '9';
    }
  }
  for (ll i = 0; i < n; ++i)
    if (s[i] != '0') {
      s = s.substr(i);
      break;
    }
  assert(is_valid(s));
  return s;
}

void solution() {
  ll T;
  cin >> T;
  string n;
  for (ll t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cin >> n;
    cout << "Case #" << t + 1 << ": " << solve(n) << '\n';
  }
}
