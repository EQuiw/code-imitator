#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const int B = 18;

ll pw10[B + 1];

void init() {
  pw10[0] = 1;
  for (int i = 1; i <= B; i++)
    pw10[i] = pw10[i - 1] * 10;
}

bool check(ll N) {
  int last = 0;
  for (int i = B; i >= 0; i--) {
    int c = N / pw10[i] % 10;
    if (c < last)
      return false;
    last = c;
  }
  return true;
}

int main() {
  init();
  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; Case++) {
    ll N;
    scanf("%lld", &N);
    N++;
    ll ans = 0;
    for (int i = 0; i <= B; i++) {
      for (int c = N / pw10[i] % 10 - 1; c >= 0; c--) {
        ll tmp = (N / pw10[i + 1] * 10 + c + 1) * pw10[i] - 1;
        if (check(tmp)) {
          ans = tmp;
          goto out;
        }
      }
    }
  out:
    printf("Case #%d: %lld\n", Case, ans);
  }
}
