#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
pair<long long, long long> K[MAXN];
int D, N;

double solve() {
  cin >> D >> N;
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    cin >> K[i].first >> K[i].second;
  }
  for (int i = 1; i < N; ++i) {
    if ((D - K[i].first) * K[ans].second > (D - K[ans].first) * K[i].second) {
      ans = i;
    }
  }
  double ret = double(1.0) * D / (D - K[ans].first) * K[ans].second;
  return ret;
}

int main() {
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    double ans = solve();
    printf("Case #%d: %.8lf\n", cas, ans);
  }
}
