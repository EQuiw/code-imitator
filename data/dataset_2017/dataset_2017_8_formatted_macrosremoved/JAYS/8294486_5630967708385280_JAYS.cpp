#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

ll D, N, K[1005], S[1005];

double solve() {
  ll maxk = D - K[0], maxs = S[0];
  for (int i = 0; i < N; i++) {
    ll curk = D - K[i], curs = S[i];
    if (maxk * curs < curk * maxs) {
      maxk = curk;
      maxs = curs;
    }
  }
  return ((double)(D * maxs)) / maxk;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%lld%lld", &D, &N);
    for (int i = 0; i < N; i++)
      scanf("%lld%lld", K + i, S + i);
    double ans = solve();
    printf("Case #%d: %.9lf\n", t, ans);
  }
  return 0;
}
