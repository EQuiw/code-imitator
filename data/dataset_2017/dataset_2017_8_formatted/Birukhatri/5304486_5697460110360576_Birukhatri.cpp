/********************************************
 *                                           *
 *    Solved By : Bir Bahadur Khatri(B'ru)   *
 *      Be Positive,be Happy.                *
 *                                           *
 *********************************************/

#define ff first
#define D double
#define sz size()
#define ss second
#define PB push_back
#define MP make_pair
#define SQR(n) (n * n)
#define CHR getchar()
#define NL printf("\n")
#include <bits/stdc++.h>
#define ULL unsigned LL
#define PI 2.0 * acos(0.0)
#define LL long long int
#define S1(a) a = in<int>()
#define SL1(a) a = in<LL>()
#define Max(a, b) ((a > b) ? a : b)
#define Min(a, b) ((a < b) ? a : b)
#define all(a) a.begin(), a.end()
#define _Max(a, b, c) Max(a, Max(b, c))
#define _Min(a, b, c) Min(a, Min(b, c))
#define cp printf("are you okay??\n")
#define SL2(a, b) a = in<LL>(), b = in<LL>()
#define F(i, a, b) for (int i = a; i < b; i++)
#define S2(a, b) a = in<int>(), b = in<int>()
#define R(i, a, b) for (int i = a - 1; i >= b; i--)
#define BitCnt(a) __builtin_popcountll(a)
#define MEM(a, val) memset(a, val, sizeof(a))
#define SL3(a, b, c) a = in<LL>(), b = in<LL>(), c = in<LL>()
#define S3(a, b, c) a = in<int>(), b = in<int>(), c = in<int>()
#define trace1(x) cerr << #x << ": " << x << endl;
#define InpOut freopen("A.in", "r", stdin), freopen("A1.out", "w", stdout)
#define trace2(x, y)                                                           \
  cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)                                                        \
  cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": "   \
       << z << endl;
#define trace4(a, b, c, d)                                                     \
  cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": "   \
       << c << " | " << #d << ": " << d << endl;
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
    return SQR(POW(B, P / 2));
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

#define MD1 1000000007ULL
#define MD2 1000000009ULL
#define MD3 1000000021ULL
#define BS1 10000019ULL
#define BS2 10000079ULL
#define BS3 10000103ULL
#define PUL pair<ULL, ULL>
#define PII pair<int, int>

#define lchild lft, l, mid
#define rchild rgt, mid + 1, r
#define ngood r<st || l> ed
#define good st <= l &&ed >= r
#define seg int mid = (l + r) / 2, lft = 2 * id, rgt = lft + 1

///         0123456789
#define MX 55
#define MOD 1000000007
#define INF 2000000000000000LL
#define EPS 1e-9
/// ==========================================////

int r, c;
LL a[MX];
LL aa[MX];
LL b[MX][MX];
vector<LL> x;
bool isok(LL m, int p) {
  for (int i = 1; i <= r; i++)
    aa[i] = a[i] * m;
  for (int i = 1; i <= r; i++) {
    if (aa[i] <= x[i - 1])
      continue;
    return 0;
  }
  return 1;
}

int ok(LL m, int p) {
  for (int i = 1; i <= r; i++)
    aa[i] = a[i] * m;
  int tot = 0;
  for (int i = 1; i <= r; i++) {
    LL y = x[i - 1];
    LL x = aa[i];

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
  LL lo = 1, hi = 1e6;
  LL an = -1;
  x.clear();
  x.PB(b[1][p]);
  if (q != -1)
    x.PB(b[2][q]);
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
  for (LL j = an;; j++) {
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
      MEM(dp, -1);
      ans = lol(1, 0);
    }

    printf("Case #%d: ", cs);
    printf("%d\n", ans);
    trace1(cs)
  }

  return 0;
}
