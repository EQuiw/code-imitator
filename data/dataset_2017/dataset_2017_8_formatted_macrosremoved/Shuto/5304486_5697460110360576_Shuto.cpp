#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

inline bool ok_1(long long int x, long long int unit) {
  x *= 10;
  unit *= 10;
  long long int near = x / unit;
  if (x >= unit * near * 9 / 10 && x <= unit * near * 11 / 10) {
    return true;
  }
  ++near;
  if (x >= unit * near * 9 / 10 && x <= unit * near * 11 / 10) {
    return true;
  }
  return false;
}

inline PI get_range(long long int x, long long int unit) {
  PI res;
  res.second = (x * 10 / 9) / unit;
  res.first = (x * 10 / 11) / unit;
  if ((x * 10 / 11) % unit > 0)
    res.first++;
  return res;
}

inline bool has_common(PI r1, PI r2) {
  return r1.second >= r2.first && r2.second >= r1.first;
}

inline bool ok_2(PI x, PI unit) {
  PI range1 = get_range(x.first, unit.first);
  PI range2 = get_range(x.second, unit.second);
  // p4(range1.F, range1.S, range2.F, range2.S);
  return has_common(range1, range2);
}

inline void solve() {
  long long int n, p;
  cin >> n >> p;
  vector<vector<long long int>> a(n, vector<long long int>(p));
  vector<long long int> r(n);
  for (long long int i = 0; i < ((long long int)(n)); i++) {
    cin >> r[i];
  }
  for (long long int i = 0; i < ((long long int)(n)); i++) {
    for (long long int j = 0; j < ((long long int)(p)); j++)
      cin >> a[i][j];
  }
  if (n == 1) {
    long long int res = 0;
    for (long long int i = 0; i < ((long long int)(p)); i++) {
      if (ok_1(a[0][i], r[0])) {
        ++res;
      }
    }
    cout << res << endl;
  } else if (n == 2) {
    long long int res = 0;
    do {
      long long int tres = 0;
      for (long long int i = 0; i < ((long long int)(p)); i++) {
        if (ok_2(make_pair(a[0][i], a[1][i]), make_pair(r[0], r[1]))) {
          ++tres;
        }
      }
      res = max(res, tres);
    } while (next_permutation(a[1].begin(), a[1].end()));
    cout << res << endl;
  } else {
    cout << 1 << endl;
  }
}

int main() {
  long long int t;
  cin >> t;
  for (long long int case_num = 0; case_num < ((long long int)(t));
       case_num++) {
    cout << "Case #" << case_num + 1 << ": ";
    solve();
  }

  return 0;
}
