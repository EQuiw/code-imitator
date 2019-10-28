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

struct z {
  int nd;
  double cs;
  z() {}
  z(int a, double b) { nd = a, cs = b; }

  bool operator<(const z &p) const { return (p.cs < cs); }
};

double d[105][105];
double e[105];
double s[105];
double ds[105];
int main() {
  freopen("A.in", "r", stdin), freopen("A1.out", "w", stdout);
  int t;
  // priority_queue<z> q;
  // q.push(z(1,2));
  // q.push(z(1,3));
  // cout<<q.top().cs<<endl;
  t = in<int>();

  for (int cs = 1; cs < t + 1; cs++) {

    int n;
    n = in<int>();
    int q;
    q = in<int>();
    for (int i = 1; i < n + 1; i++)
      cin >> e[i] >> s[i];

    for (int i = 1; i < n + 1; i++)
      for (int j = 1; j < n + 1; j++) {
        cin >> d[i][j];
        if (d[i][j] < 0)
          d[i][j] = 1e18;
      }
    for (int k = 1; k < n + 1; k++)
      for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < n + 1; j++)
          d[i][j] =
              ((d[i][j] < d[i][k] + d[k][j]) ? d[i][j] : d[i][k] + d[k][j]);
    // NL;cout<<d[1][4]<< " ****** "<<d[2][1]<<endl;

    printf("Case #%d:", cs);
    while (q--) {
      int st, ed;
      cin >> st >> ed;

      for (int i = 1; i < n + 1; i++)
        ds[i] = 1e18;

      ds[st] = 0.0;
      priority_queue<z> q;
      q.push(z(st, 0));
      while (q.size()) {
        z tp = q.top();
        q.pop();
        int u = tp.nd;

        // trace2(u,tp.cs)

        for (int i = 1; i < n + 1; i++) {
          // trace4(u,i,e[u],d[u][i])
          if (e[u] >= d[u][i]) {
            double cs = d[u][i] / s[u];
            if (ds[i] > (ds[u] + cs)) {
              ds[i] = (ds[u] + cs);
              q.push(z(i, ds[i]));
            }
          }
        }
      }
      printf(" ");
      printf("%.10lf", ds[ed]);
    }
    printf("\n");
    cerr << "cs"
         << ": " << cs << endl;
  }

  return 0;
}
///============= Thank You ===================///
