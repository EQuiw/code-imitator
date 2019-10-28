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
lld A[700005], B[700005], C[700005];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;

int main() {
  lld T, i, n, m, p, j, l, e, r, b, c, k, q, a, d, w, x, y, v, z, t, curr, prev,
      sum, ans, pos, val, countA, secondMin, indicator;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld:\n", testC);
    scanf("%lld%lld", &r, &c);
    for (long long int i = (0); i <= (r - 1); ++i)
      cin >> S[i];
    for (long long int i = (0); i <= (r - 1); ++i)
      A[i] = 0;
    for (long long int i = (0); i <= (r - 1); ++i) {
      x = -1;
      for (long long int j = (0); j <= (c - 1); ++j) {
        if (S[i][j] != '?') {
          x = j;
          break;
        }
      }
      if (x != -1) {
        A[i] = 1;
        for (long long int j = (0); j <= (c - 1); ++j) {
          if (S[i][j] == '?') {
            S[i][j] = S[i][x];
          } else
            x = j;
        }
      }
    }
    y = -1;
    for (long long int i = (0); i <= (r - 1); ++i) {
      if (A[i] == 1) {
        y = i;
        break;
      }
    }
    for (long long int i = (0); i <= (r - 1); ++i) {
      if (A[i] == 0) {
        for (long long int j = (0); j <= (c - 1); ++j)
          S[i][j] = S[y][j];
      } else
        y = i;
    }
    for (long long int i = (0); i <= (r - 1); ++i)
      cout << S[i] << endl;
  }
  return 0;
}
