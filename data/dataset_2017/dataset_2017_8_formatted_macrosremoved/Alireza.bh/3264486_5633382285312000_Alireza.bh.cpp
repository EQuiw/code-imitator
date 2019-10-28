
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
    cin >> s;
    string res = s;
    for (int(i) = 0; (i) < (s.size() - 1); (i)++) {
      string temp(s.size() - i - 1, s[i]);
      if (temp <= s.substr(i + 1))
        continue;
      res[i]--;
      for (int(j) = (i + 1); (j) < (s.size()); (j)++)
        res[j] = '9';
      break;
    }
    while (res[0] == '0')
      res = res.substr(1);
    cout << res << endl;
  }
}
