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
// string S[lim];
double A[700005], B[700005], C[700005], E[700005], S[700005];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;
double Dis[103][103], dp[103][103], Query[700005], From[103][103];

int main() {
  lld T, i, n, m, p, j, l, e, r, b, c, k, q, a, d, w, x, y, u, v, z, t, curr,
      prev, sum, ans, pos, val, countA, secondMin, indicator;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld: ", testC);
    scanf("%lld%lld", &n, &q);
    for (long long int i = (1); i <= (n); ++i)
      scanf("%lf%lf", &E[i], &S[i]);
    for (long long int i = (1); i <= (n); ++i) {
      for (long long int j = (1); j <= (n); ++j) {
        scanf("%lf", &Dis[i][j]);
        if (Dis[i][j] == -1)
          Dis[i][j] = mod * 1000000;
      }
      Dis[i][i] = 0;
    }
    for (long long int k = (1); k <= (n); ++k)
      for (long long int i = (1); i <= (n); ++i)
        for (long long int j = (1); j <= (n); ++j)
          Dis[i][j] = min(Dis[i][j], Dis[i][k] + Dis[k][j]);
    while (q--) {
      scanf("%lld%lld", &u, &v);
    }
    for (long long int i = (1); i <= (n); ++i)
      for (long long int j = (i + 1); j <= (n); ++j) {
        double r = 0;
        for (long long int k = (i); k <= (j - 1); ++k)
          r += Dis[k][k + 1];
        From[i][j] = r;
      }
    // if(testC!=57) continue;
    // rep(i,1,n) rep(j,i+1,n) if(Dis[i][j]!=From[i][j]){
    //     Error3(i,j,"fuck");
    //     Error2(Dis[i][j],From[i][j]);
    // }
    Query[n] = 0;
    for (long long int i = (n - 1); i >= (1); --i) {
      Query[i] = mod * 1000000;
      for (long long int j = (i + 1); j <= (n); ++j)
        if (E[i] >= From[i][j])
          Query[i] = min(Query[i], From[i][j] / S[i] + Query[j]);
    }
    printf("%lf\n", Query[1]);
  }
  return 0;
}
