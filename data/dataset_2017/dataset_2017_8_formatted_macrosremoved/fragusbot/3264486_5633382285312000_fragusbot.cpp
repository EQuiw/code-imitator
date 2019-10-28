#include <bits/stdc++.h>

using namespace std;

bool check(int n) {
  while (n > 0) {
    if (n % 10 < n / 10 % 10) {
      return false;
    }
    n /= 10;
  }
  return true;
}

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    printf("Case #%d: ", cc);
    int n;
    scanf("%d", &n);
    int ans = n;
    while (!check(ans)) {
      --ans;
    }
    printf("%d\n", ans);
  }
}
