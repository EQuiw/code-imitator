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
lld A[700005], B[700005], C[700005];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;

int main() {
  lld T, i, n, m, p, j, l, e, r, b, c, k, q, a, d, w, x, y, v, z, t, curr, prev,
      sum, ans, pos, val, countA, secondMin, indicator;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld: ", testC);
    string S;
    cin >> S;
    scanf("%lld", &k);
    n = S.size();
    for (long long int i = (0); i <= (n - 1); ++i)
      A[i] = 0;
    curr = 0;
    ans = 0;
    p = 1;
    for (long long int i = (0); i <= (n - 1); ++i) {
      curr += A[i];
      t = (curr + (S[i] == '+')) % 2;
      if (t != 1) {
        if (i + k - 1 >= n)
          p = 0;
        A[i + k]++;
        curr++;
        ans++;
      }
    }
    if (p == 0)
      printf("IMPOSSIBLE\n");
    else
      printf("%lld\n", ans);
  }
  return 0;
}
