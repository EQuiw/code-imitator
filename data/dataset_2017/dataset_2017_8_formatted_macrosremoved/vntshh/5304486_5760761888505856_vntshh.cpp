#include <bits/stdc++.h>
using namespace std;

using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = 1000000007) {
  lld ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % mod;
    exp >>= 1, base = (base * base) % mod;
  }
  return ans;
}
typedef vector<lld> vlld;
typedef pair<lld, lld> plld;
typedef map<lld, lld> mlld;
typedef set<lld> slld;

lld r, c;
char a[30][30];
void go(lld x, lld y) {
  char c = a[x][y];
  lld l = 1, r = 1;
  while (1) {
    if (a[x][y - l] != '?')
      break;
    a[x][y - l] = c;
    l++;
  }
  while (1) {
    if (a[x][y + r] != '?')
      break;
    a[x][y + r] = c;
    r++;
  }
}
int main() {
  freopen("123.in", "r", stdin);
  freopen("1234.out", "w", stdout);
  lld t;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    for (lld i = 0; i < 30; i++)
      for (lld j = 0; j < 30; j++)
        a[i][j] = '-';
    cin >> r >> c;
    for (lld i = 1; i < r + 1; i++)
      for (lld j = 1; j < c + 1; j++)
        cin >> a[i][j];
    for (lld i = 1; i < r + 1; i++)
      for (lld j = 1; j < c + 1; j++)
        if (a[i][j] >= 'A' and a[i][j] <= 'Z')
          go(i, j);
    int ind = -1, flag = 0;
    for (lld i = 1; i < r + 1; i++) {
      for (lld j = 1; j < c + 1; j++)
        if (a[i][j] != '?') {
          ind = i;
          flag = 1;
          break;
        }
      if (flag == 1)
        break;
    }
    for (lld i = 1; i < ind; i++) {
      flag = 0;
      for (lld j = 1; j < c + 1; j++)
        if (a[i][j] != '?') {
          flag = 1;
          break;
        }
      if (flag == 0)
        for (lld j = 1; j < c + 1; j++)
          a[i][j] = a[ind][j];
    }
    for (lld i = ind; i < r + 1; i++) {
      flag = 0;
      for (lld j = 1; j < c + 1; j++)
        if (a[i][j] != '?') {
          flag = 1;
          break;
        }
      if (flag == 0)
        for (lld j = 1; j < c + 1; j++)
          a[i][j] = a[i - 1][j];
    }
    cout << "Case #" << tt << ":\n";
    for (lld i = 1; i < r + 1; i++) {
      for (lld j = 1; j < c + 1; j++)
        cout << a[i][j];
      printf("\n");
    }
  }
  return 0;
}
