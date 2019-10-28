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
lld A[700005], B[700005], C[700005];
// unordered_map<lld,lld> M,X;
// map<lld,lld> M;
char S[1003];

int main() {
  lld T, i, n, m, p, j, l, e, r, b, c, k, q, a, d, w, x, y, u, v, z, t, curr,
      prev, sum, ans, pos, val, countA, secondMin, indicator;
  scanf("%lld", &T);
  for (long long int testC = (1); testC <= (T); ++testC) {
    printf("Case #%lld: ", testC);
    scanf("%lld", &n);
    for (long long int i = (1); i <= (6); ++i)
      scanf("%lld", &A[i]);
    t = 1;
    a = A[1];
    b = A[3];
    c = A[5];
    if (a > n / 2 || b > n / 2 || c > n / 2)
      t = 0;
    // if(testC==76) Error4(a,b,c,n);
    if (n == 1)
      t = 1;
    if (t == 0) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    char R, Y, B;
    R = 'R';
    Y = 'Y';
    B = 'B';
    if (a < b) {
      swap(a, b);
      swap(R, Y);
    }
    if (b < c) {
      swap(b, c);
      swap(Y, B);
    }
    if (a < b) {
      swap(a, b);
      swap(R, Y);
    }
    for (long long int i = (1); i <= (n); ++i)
      S[i] = 'A';
    for (lld i = 1; a > 0; i += 2) {
      S[i] = R;
      a--;
    }
    if (n % 2 == 0)
      x = n;
    else
      x = n - 1;
    while (b > 0) {
      S[x] = Y;
      x -= 2;
      b--;
    }
    for (long long int i = (1); i <= (n); ++i)
      if (S[i] == 'A')
        S[i] = B;
    for (long long int i = (1); i <= (n); ++i)
      printf("%c", S[i]);
    // rep(i,1,n-1) if(S[i]==S[i+1]) Error4(a,b,c,"fuck");
    printf("\n");
  }
  return 0;
}
