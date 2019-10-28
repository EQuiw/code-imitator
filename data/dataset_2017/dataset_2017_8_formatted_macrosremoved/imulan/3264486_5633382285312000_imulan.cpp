#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
bool is_tidy(string s) {
  int n = s.size();
  for (int(i) = 0; (i) < (int)(n - 1); ++(i))
    if (s[i] > s[i + 1])
      return false;
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
  for (int(i) = 0; (i) < (int)(n - 1); ++(i)) {
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
  for (int(t) = 0; (t) < (int)(T); ++(t))
    printf("Case #%d: %lld\n", t + 1, solve());
  return 0;
}
