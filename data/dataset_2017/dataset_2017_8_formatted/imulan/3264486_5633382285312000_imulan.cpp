#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, n) for (int(i) = 0; (i) < (int)(n); ++(i))
#define each(itr, c)                                                           \
  for (__typeof(c.begin()) itr = c.begin(); itr != c.end(); ++itr)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second

bool is_tidy(string s) {
  int n = s.size();
  rep(i, n - 1) if (s[i] > s[i + 1]) return false;
  return true;
}

ll solve() {
  string s;
  cin >> s;

  ll S = atoll(s.c_str());
  if (is_tidy(s))
    return S;

  int n = s.size();

  ll ret = -1;
  rep(i, n - 1) {
    if (s[i] == '0')
      continue;

    string t = s.substr(0, i);
    t += s[i] - 1;
    while (t.size() < n)
      t += "9";

    if (is_tidy(t))
      ret = max(ret, atoll(t.c_str()));
  }

  return ret;
}

int main() {
  int T;
  cin >> T;
  rep(t, T) printf("Case #%d: %lld\n", t + 1, solve());
  return 0;
}
