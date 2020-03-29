#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int P;
int N;
int G[105];
int ct[5];

int solve() {
  cin >> N >> P;
  memset(ct, 0, sizeof(ct));
  for (int i = 0; i < N; ++i) {
    cin >> G[i];
    G[i] %= P;
    ++ct[G[i]];
  }
  int ans = N;
  if (P == 2) {
    ans -= ct[1] / 2;
  } else if (P == 3) {
    int a = min(ct[1], ct[2]);
    ans -= a;
    ct[1] -= a;
    ct[2] -= a;
    int b = ct[1] + ct[2];
    ans -= b / 3 * 2;
    if (b % 3 == 2)
      --ans;
  } else {
    int a = min(ct[1], ct[3]);
    ans -= a;
    ct[1] -= a;
    ct[2] -= a;
    ans -= ct[2] / 2;
    int b = ct[1] + ct[2];
  }
  return ans;
}

int main() {
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int ans = solve();
    printf("Case #%d: %d\n", cas, ans);
  }
}
