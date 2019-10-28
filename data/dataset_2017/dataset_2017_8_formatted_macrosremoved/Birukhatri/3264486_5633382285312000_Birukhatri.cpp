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
template <typename T> long long int isLeft(T a, T b, T c) {
  return (a.x - b.x) * (b.y - c.y) - (b.x - c.x) * (a.y - b.y);
}
long long ModInverse(long long number, long long MOD) {
  return Bigmod(number, MOD - 2, MOD);
}
bool isConst(char ch) {
  if (isalpha(ch) && !isVowel(ch))
    return true;
  return false;
}
int toInt(string s) {
  int sm;
  stringstream second(s);
  second >> sm;
  return sm;
}
///**********************************************************//
///         0123456789

/// ==========================================////
int a[20], ln;
void make(long long int n) {
  ln = 0;
  while (n) {
    a[ln++] = n % 10;
    n /= 10;
  }
  reverse(a, a + ln);
}

long long int dp[20][2][10];

long long int lol(int p, int ch, int pv) {
  if (p == ln) {
    return 1;
  }
  long long int &res = dp[p][ch][pv];
  if (res != -1)
    return res;

  res = 0;
  int hi = a[p];
  if (ch)
    hi = 9;
  for (int i = pv; i <= hi; i++) {
    res += lol(p + 1, ch | (i < hi), i);
  }
  return res;
}

long long int koto(long long int n) {
  make(n);
  memset(dp, -1, sizeof(dp));
  return lol(0, 0, 0);
}

int main() {

  freopen("A.in", "r", stdin);
  freopen("A1.out", "w", stdout);
  int t;
  t = in<int>();

  for (int cs = 1; cs < t + 1; cs++) {
    long long int n;
    cin >> n;

    long long int tot = koto(n);

    long long int lo = 1, hi = n;
    long long int ans;

    while (lo <= hi) {
      long long int mid = (lo + hi) / 2;
      long long int k = koto(mid);
      if (k == tot) {
        ans = mid;
        hi = mid - 1;
      } else
        lo = mid + 1;
    }

    printf("Case #%d: %lld\n", cs, ans);
  }

  return 0;
}

///============= Thank You ===================///
