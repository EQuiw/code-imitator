#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
long long mod = 1e9 + 7;
long long INF = 1e7;
double EPS = 1e-12;
typedef long long int lld;
double tick() {
  static clock_t oldt;
  clock_t newt = clock();
  double diff = 1.0 * (newt - oldt) / CLOCKS_PER_SEC;
  oldt = newt;
  return diff;
}
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
string S[700005];
lld A[700005], B[700005], Quan[1003][1003];
double C[700005];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;

bool valid(lld n) {
  lld t, low, high, mid;
  double curr, val, l = 0.9 - EPS, h = 1.10 + EPS;
  low = 1;
  high = Quan[1][B[1]];
  // rep(i,1,n) Error3(i,B[i],Quan[i][B[i]]);
  while (low <= high) {
    mid = low + (high - low) / 2;
    t = 1;
    for (long long int i = (1); i <= (n); ++i) {
      val = A[i] * mid;
      curr = Quan[i][B[i]] / val;
      // if(mid==1) Error4(A[i],B[i],val,curr);
      if (curr < l)
        t = 2;
      if (curr > h)
        t = 3;
    }
    // Error2(mid,t);
    if (t == 1)
      return true;
    if (t == 3)
      low = mid + 1;
    if (t == 2)
      high = mid - 1;
  }
  return false;
}

int main() {
  lld T, i, n, m, p, j, l, e, r, b, c, k, q, a, d, w, x, y, v, z, t, curr, prev,
      sum, ans, pos, val, countA, secondMin, indicator;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld: ", testC);
    scanf("%lld%lld", &n, &p);
    for (long long int i = (1); i <= (n); ++i)
      scanf("%lld", &A[i]);
    ans = 0;
    for (long long int i = (1); i <= (n); ++i)
      B[i] = 1;
    for (long long int i = (1); i <= (n); ++i)
      for (long long int j = (1); j <= (p); ++j)
        scanf("%lld", &Quan[i][j]);
    for (long long int i = (1); i <= (n); ++i)
      sort(Quan[i] + 1, Quan[i] + p + 1);
    while (true) {
      if (valid(n)) {
        ans++;
        for (long long int i = (1); i <= (n); ++i)
          B[i]++;
      } else {
        for (long long int i = (1); i <= (n); ++i)
          C[i] = Quan[i][B[i]] * 1.0 / A[i];
        x = 1;
        for (long long int i = (2); i <= (n); ++i)
          if (C[i] < C[x])
            x = i;
        B[x]++;
      }
      t = 0;
      for (long long int i = (1); i <= (n); ++i)
        t += (B[i] > p);
      if (t > 0)
        break;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
