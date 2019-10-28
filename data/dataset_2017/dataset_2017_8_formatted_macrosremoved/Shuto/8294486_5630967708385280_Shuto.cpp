#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

long long int pos[1010];
long long int speed[1010];

inline void solve() {
  long long int d, n;
  cin >> d >> n;
  for (long long int i = 0; i < ((long long int)(n)); i++) {
    cin >> pos[i] >> speed[i];
  }
  double res = 0;
  for (long long int i = 0; i < ((long long int)(n)); i++) {
    res = max(res, (d - pos[i]) * 1.0 / speed[i]);
  }
  printf("%.12f\n", d / res);
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
