#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.out", "w", stdout);
  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    long long x, K;
    cin >> x >> K;

    long long KK = K;
    int i = 0;
    for (; (1LL << i) < K; i++) {
      K -= (1LL << i);
    }
    x -= (KK - K);
    long long y = x / (1 << i) + (K <= (x % (1 << i)));
    printf("Case #%d: %I64d %I64d\n", _, y / 2, (y - 1) / 2);
  }
  return 0;
}
