
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
    string s;
    int k;
    cin >> s >> k;
    int res = 0;
    for (int(i) = 0; (i) < (s.size() - k + 1); (i)++) {
      if (s[i] == '+')
        continue;
      for (int(j) = (i); (j) < (i + k); (j)++)
        s[j] = (s[j] == '+' ? '-' : '+');
      res++;
    }
    bool ok = true;
    for (int(i) = 0; (i) < (s.size()); (i)++)
      if (s[i] == '-')
        ok = false;
    if (ok)
      cout << res << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
}
