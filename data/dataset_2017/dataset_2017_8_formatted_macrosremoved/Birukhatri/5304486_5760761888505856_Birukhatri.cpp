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

char second[55][55];
int n, m;

void lol(int x, int y, char ch) {
  if (y < 1)
    return;
  if (second[x][y] != '?')
    return;
  second[x][y] = ch;
  lol(x, y - 1, ch);
}

void lol1(int x, int y, char ch) {
  if (x > n)
    return;
  if (second[x][y] != '?')
    return;
  second[x][y] = ch;
  lol(x, y - 1, ch);
  lol1(x + 1, y, ch);
}

void lol2(int x, int y, int ch) {
  if (x < 1)
    return;
  if (second[x][y] != '?')
    return;
  second[x][y] = ch;
  lol(x, y - 1, ch);
  lol2(x - 1, y, ch);
}

int main() {
  freopen("A.in", "r", stdin);
  freopen("A1.out", "w", stdout);

  int tc;
  scanf("%d", &tc);

  for (int cas = 1; cas <= tc; cas++) {

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
      scanf("%s", &second[i][1]);
    }

    for (int j = 1; j <= m; j++) {
      for (int i = 1; i <= n; i++) {
        if ((second[i][j] != '?')) {
          lol1(i + 1, j, second[i][j]);
          lol2(i - 1, j, second[i][j]);
          lol(i, j - 1, second[i][j]);
        }
      }
    }

    for (int j = 1; j <= m; j++) {
      for (int i = 1; i <= n; i++) {
        if (second[i][j] == '?')
          second[i][j] = second[i][j - 1];
      }
    }

    printf("Case #%d:\n", cas);

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        printf("%c", second[i][j]);
      }
      puts("");
    }
    cerr << "cas"
         << ": " << cas << endl;
  }
}
