
#pragma comment(linker, "/STACK:100000000000")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcas;
  cin >> Tcas;
  for (int(cas) = 0; (cas) < (Tcas); (cas)++) {
    printf("Case #%d: ", cas + 1);
    string s[30];
    int n, m;
    cin >> n >> m;
    for (int(i) = 0; (i) < (n); (i)++)
      cin >> s[i];
    for (int(i) = 0; (i) < (n); (i)++) {
      char lastchar = '?';
      for (int(j) = 0; (j) < (m); (j)++) {
        if (s[i][j] != '?') {
          lastchar = s[i][j];
          continue;
        }
        if (lastchar != '?')
          s[i][j] = lastchar;
      }
      lastchar = '?';
      for (int j = m - 1; j >= 0; j--) {
        if (s[i][j] != '?') {
          lastchar = s[i][j];
          continue;
        }
        if (lastchar != '?')
          s[i][j] = lastchar;
      }
    }
    for (int(j) = 0; (j) < (m); (j)++) {
      char lastchar = '?';
      for (int(i) = 0; (i) < (n); (i)++) {
        if (s[i][j] != '?') {
          lastchar = s[i][j];
          continue;
        }
        if (lastchar != '?')
          s[i][j] = lastchar;
      }
      lastchar = '?';
      for (int i = n - 1; i >= 0; i--) {
        if (s[i][j] != '?') {
          lastchar = s[i][j];
          continue;
        }
        if (lastchar != '?')
          s[i][j] = lastchar;
      }
    }
    cout << endl;
    for (int(i) = 0; (i) < (n); (i)++)
      cout << s[i] << endl;
  }
}
