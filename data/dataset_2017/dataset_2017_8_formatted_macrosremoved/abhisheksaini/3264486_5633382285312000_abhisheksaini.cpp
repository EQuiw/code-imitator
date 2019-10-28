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
  for (long long int i = (1); i <= (9); ++i)
    A[1][i] = i;
  for (long long int i = (2); i <= (18); ++i)
    for (long long int j = (1); j <= (9); ++j)
      A[i][j] = A[i - 1][j] * 10 + j;
  B[0] = 1;
  for (long long int i = (1); i <= (18); ++i)
    B[i] = B[i - 1] * 10;
  A[19][1] = A[18][1] * 10 + 1;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld: ", testC);
    scanf("%lld", &n);
    t = countDig(n);
    if (n < A[t][1])
      printf("%lld\n", A[t - 1][9]);
    else {
      curr = 0;
      a = 1;
      bool flag;
      for (long long int j = (t); j >= (1); --j) {
        flag = false;
        for (long long int i = (a); i <= (9); ++i) {
          val = curr + A[j][i];
          if (val > n) {
            curr = curr + (i - 1) * B[j - 1];
            a = i - 1;
            flag = true;
            break;
          }
        }
        if (!flag) {
          curr = curr + 9 * B[j - 1];
          a = 9;
        }
      }
      printf("%lld\n", curr);
    }
  }
  return 0;
}
