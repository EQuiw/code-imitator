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

int ar[7];

int br[1002];
int n;
int isok(int a, int b, int c) {

  for (int i = 2; i < n && a;) {
    if (br[i])
      i++;
    else if ((br[i - 1] == 1) || (br[i + 1] == 1))
      i++;
    else {
      br[i] = 1;
      i += 2;
      a--;
    }
  }
  for (int i = n - 1; i >= 1 && b;) {
    if (br[i])
      i--;
    else if ((br[i - 1] == 2) || (br[i + 1] == 2))
      i--;
    else {
      br[i] = 2;
      i -= 2;
      b--;
    }
  }

  for (int i = 2; i < n && c;) {
    if (br[i])
      i++;
    else if ((br[i - 1] == 3) || (br[i + 1] == 3))
      i++;
    else {
      br[i] = 3;
      i += 2;
      c--;
    }
  }
  for (int i = 1; i < n; i++) {
    if (br[i] == br[i + 1])
      return 0;
  }
  if ((a + b + c))
    return 0;

  for (int i = 1; i < n + 1; i++) {
    if (br[i] == 1)
      cout << "R";
    else if (br[i] == 2)
      cout << "Y";
    else
      cout << "B";
  }
  printf("\n");
  return 1;
}

int main() {
  freopen("A.in", "r", stdin), freopen("A1.out", "w", stdout);
  int t;
  t = in<int>();

  for (int cs = 1; cs < t + 1; cs++) {
    n = in<int>();
    for (int i = 1; i < 6 + 1; i++)
      cin >> ar[i];

    ar[2] = ar[3];
    ar[3] = ar[5];
    printf("Case #%d: ", cs);
    int fl = 0;
    for (int i = 1; i <= 3; i++) {
      for (int j = i + 1; j <= 3; j++) {
        if (ar[i] && ar[j]) {
          memset(br, 0, sizeof(br));
          br[1] = i;
          br[n] = j;
          ar[i]--;
          ar[j]--;
          if (isok(ar[1], ar[2], ar[3])) {
            fl = 1;
            break;
          }
          ar[i]++;
          ar[j]++;
        }
      }
      if (fl)
        break;
    }

    if (!fl)
      cout << "IMPOSSIBLE\n";
    cerr << "cs"
         << ": " << cs << endl;
  }

  return 0;
}
///============= Thank You ===================///
