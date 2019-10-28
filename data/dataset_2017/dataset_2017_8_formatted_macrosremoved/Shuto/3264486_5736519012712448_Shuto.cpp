#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

map<char, char> m;

inline void flip(string &s, long long int idx, long long int l) {
  for (long long int i = (long long int)(idx); i < ((long long int)(idx + l));
       i++) {
    s[i] = m[s[i]];
  }
}

inline void solve() {
  string s;
  long long int l;
  cin >> s >> l;
  long long int res = 0;
  for (long long int i = 0;
       i < ((long long int)(((long long int)(s).size()) - l + 1)); i++) {
    if (s[i] == '-') {
      flip(s, i, l);
      ++res;
    }
  }
  for (long long int i = 0; i < ((long long int)(((long long int)(s).size())));
       i++) {
    if (s[i] != '+') {
      cout << "IMPOSSIBLE";
      return;
    }
  }
  cout << res;
}

int main() {
  m['-'] = '+';
  m['+'] = '-';
  long long int t;
  cin >> t;
  for (long long int case_num = 0; case_num < ((long long int)(t));
       case_num++) {
    cout << "Case #" << case_num + 1 << ": ";
    solve();
    cout << endl;
  }

  return 0;
}
