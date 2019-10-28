/********************************************
 *                                           *
 *    Solved By : Bir Bahadur Khatri(B'ru)   *
 *      Be Positive,be Happy.                *
 *                                           *
 *********************************************/
#include <bits/stdc++.h>
using namespace std;
template <typename T> T in() {
  char ch;
  T n = 0;
  bool ng = false;
  while (1) {
    ch = getchar();
    if (ch == '-') {
      ng = true;
      ch = getchar();
      break;
    }
    if (ch >= '0' && ch <= '9')
      break;
  }
  while (1) {
    n = n * 10 + (ch - '0');
    ch = getchar();
    if (ch < '0' || ch > '9')
      break;
  }
  return (ng ? -n : n);
}
template <typename T> inline T POW(T B, T P) {
  if (P == 0)
    return 1;
  if (P & 1)
    return B * POW(B, P - 1);
  else
    return (POW(B, P / 2) * POW(B, P / 2));
}
template <typename T> inline T Gcd(T a, T b) {
  if (a < 0)
    return Gcd(-a, b);
  if (b < 0)
    return Gcd(a, -b);
  return (b == 0) ? a : Gcd(b, a % b);
}
template <typename T> inline T Lcm(T a, T b) {
  if (a < 0)
    return Lcm(-a, b);
  if (b < 0)
    return Lcm(a, -b);
  return a * (b / Gcd(a, b));
}
long long Bigmod(long long base, long long power, long long MOD) {
  long long ret = 1;
  while (power) {
    if (power & 1)
      ret = (ret * base) % MOD;
    base = (base * base) % MOD;
    power >>= 1;
  }
  return ret;
}
bool isVowel(char ch) {
  ch = toupper(ch);
  if (ch == 'A' || ch == 'U' || ch == 'I' || ch == 'O' || ch == 'E')
    return true;
  return false;
}
long long ModInverse(long long number, long long MOD) {
  return Bigmod(number, MOD - 2, MOD);
}
bool isConst(char ch) {
  if (isalpha(ch) && !isVowel(ch))
    return true;
  return false;
}
///**********************************************************//
///         0123456789

/// ==========================================////

int r, c;
long long int a[55];
long long int aa[55];
long long int b[55][55];
vector<long long int> x;
bool isok(long long int m, int p) {
  for (int i = 1; i <= r; i++)
    aa[i] = a[i] * m;
  for (int i = 1; i <= r; i++) {
    if (aa[i] <= x[i - 1])
      continue;
    return 0;
  }
  return 1;
}

int ok(long long int m, int p) {
  for (int i = 1; i <= r; i++)
    aa[i] = a[i] * m;
  int tot = 0;
  for (int i = 1; i <= r; i++) {
    long long int y = x[i - 1];
    long long int x = aa[i];

    if (x <= y) {
      x *= 110;
      y *= 100;
      if (x >= y) {
        tot++;
      }
    } else {
      y *= 100;
      x *= 90;
      if (x > y)
        return 2;
      tot++;
    }
  }
  if (tot == r)
    return 1;
  return 0;
}

int solve(int p, int q) {
  long long int lo = 1, hi = 1e6;
  long long int an = -1;
  x.clear();
  x.push_back(b[1][p]);
  if (q != -1)
    x.push_back(b[2][q]);
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (isok(mid, p)) {
      an = mid;
      lo = mid + 1;
    } else
      hi = mid - 1;
  }
  if (an == -1)
    return 0;
  for (long long int j = an;; j++) {
    int tp = ok(j, p);
    // trace2(j,tp)
    if (tp == 1)
      return 1;
    if (tp == 2)
      return 0;
  }
  return 0;
}

int dp[9][1000];

int lol(int p, int m) {
  if (p == (c + 1))
    return 0;
  int &res = dp[p][m];
  if (res != -1)
    return res;

  res = lol(p + 1, m);
  for (int i = 0; i < c; i++) {
    if ((m & (1 << i)))
      continue;
    int tp = solve(p, i + 1);
    if (tp)
      res = max(res, 1 + lol(p + 1, m | (1 << i)));
  }
  return res;
}

int main() {
  int t;
  freopen("A.in", "r", stdin), freopen("A1.out", "w", stdout);
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {

    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        cin >> b[i][j];
      }
    }
    int ans = 0;
    if (r == 1) {
      for (int i = 1; i <= c; i++) {
        int tp = solve(i, -1);
        ans += tp;
      }
    } else {
      memset(dp, -1, sizeof(dp));
      ans = lol(1, 0);
    }

    printf("Case #%d: ", cs);
    printf("%d\n", ans);
    cerr << "cs"
         << ": " << cs << endl;
  }

  return 0;
}
