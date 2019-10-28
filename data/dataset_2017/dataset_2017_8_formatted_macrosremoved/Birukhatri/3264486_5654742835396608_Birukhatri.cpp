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

int main() {

  freopen("A.in", "r", stdin);
  freopen("A1.out", "w", stdout);
  int t;
  t = in<int>();

  for (int cs = 1; cs < t + 1; cs++) {

    priority_queue<int> q;
    long long int n, x;
    cin >> n >> x;
    q.push(n);
    x--;

    while (x > 0 && q.size()) {
      x--;
      long long int x = q.top();
      q.pop();
      if (x % 2 == 0) {
        if (x / 2 - 1 > 0)
          q.push(x / 2 - 1);
        if (x / 2)
          q.push(x / 2);
      } else {
        if (x / 2)
          q.push(x / 2), q.push(x / 2);
      }
    }
    long long int a = 0, b = 0;
    if (q.size()) {
      n = q.top();
      if (n % 2) {
        a = n / 2;
        b = n / 2;
      } else {
        a = max(0LL, n / 2 - 1);
        b = n / 2;
      }
    }
    printf("Case #%d: ", cs);
    cout << b << " " << a << endl;
    cerr << "cs"
         << ": " << cs << endl;
  }

  return 0;
}

///============= Thank You ===================///
