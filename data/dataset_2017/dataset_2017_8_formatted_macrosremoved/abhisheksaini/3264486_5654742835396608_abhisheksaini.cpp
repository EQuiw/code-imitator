#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
long long mod = 1e9 + 7;
long long INF = 1e7;
double EPS = 1e-12;
typedef long long int lld;
typedef pair<lld, lld> PA;

lld powP(lld a, lld b) {
  if (b == 0)
    return 1 % mod;
  lld k;
  k = powP(a, b / 2);
  k = k * k % mod;
  if (b % 2 == 0)
    return k;
  else
    return a * k % mod;
}

bool bitSet(lld n, lld i) {
  if ((n & (1LL << i)) != 0)
    return true;
  else
    return false;
}

lld findGcd(lld a, lld b) {
  if (a == 0)
    return b;
  else
    return findGcd(b % a, a);
}

// inline lld sqr(lld x) { return x * x; }
// unordered_map<lld,lld>::iterator it;
// std::ios::sync_with_stdio(false);
// priority_queue<PA> Q;
// lld dp[1<<18];
// vector<lld> V[lim];
// string S[lim];
lld A[23][12], B[700005], C[700005];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;

lld countDig(lld n) {
  lld ans = 0;
  while (n > 0) {
    ans++;
    n /= 10;
  }
  return ans;
}

int main() {
  lld T, i, n, m, p, j, l, e, r, b, c, k, q, a, d, w, x, y, v, z, t, curr, prev,
      sum, ans, pos, val, countA, secondMin, indicator;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld: ", testC);
    scanf("%lld%lld", &n, &k);
    multiset<PA> S;
    S.insert({-(n - 1) / 2, -n / 2});
    PA pio;
    for (long long int i = (1); i <= (k - 1); ++i) {
      pio = *(S.begin());
      S.erase(S.begin());
      if (pio.first != 0)
        S.insert({-(-pio.first - 1) / 2, pio.first / 2});
      if (pio.second != 0)
        S.insert({-(-pio.second - 1) / 2, pio.second / 2});
    }
    pio = *(S.begin());
    printf("%lld %lld\n", -pio.second, -pio.first);
  }
  return 0;
}
