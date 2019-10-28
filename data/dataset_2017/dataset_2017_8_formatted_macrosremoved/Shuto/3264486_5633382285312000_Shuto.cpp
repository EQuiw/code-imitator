#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

map<char, char> m;

inline bool ok(long long int n) {
  string s = to_string(n);
  string ss = s;
  sort((ss).begin(), (ss).end());
  return ss == s;
}

inline void solve() {
  long long int n;
  cin >> n;
  while (!ok(n))
    --n;
  cout << n;
}

int main() {
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
