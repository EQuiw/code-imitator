
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

int f2(vector<int> v) {
  int odd = 0, even = 0;
  for (int(i) = 0; (i) < (v.size()); (i)++)
    if (v[i] % 2)
      odd++;
    else
      even++;
  return even + (odd + 1) / 2;
}
int f3(vector<int> v) {
  int res = 0;
  int rem1 = 0;
  int rem2 = 0;
  // int one=0;
  for (int(i) = 0; (i) < (v.size()); (i)++) {
    if (v[i] % 3 == 0) {
      res++;
      continue;
    }
    // if(v[i]==1) {one++;continue;}
    if (v[i] % 3 == 2)
      rem2++;
    else
      rem1++;
  }
  if (rem2 < rem1)
    swap(rem2, rem1);
  res += rem1;
  rem2 -= rem1;
  res += rem2 / 3;
  if (rem2 % 3 != 0)
    res++;
  return res;
}

int f4(vector<int> v) { return 0; }
int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcas;
  cin >> Tcas;
  for (int(cas) = 0; (cas) < (Tcas); (cas)++) {
    printf("Case #%d: ", cas + 1);
    int n, p;
    cin >> n >> p;
    vector<int> v;
    for (int(i) = 0; (i) < (n); (i)++) {
      int k;
      cin >> k;
      v.push_back(k);
    }
    if (p == 2)
      cout << f2(v) << endl;
    if (p == 3)
      cout << f3(v) << endl;
    if (p == 4)
      cout << f4(v) << endl;
  }
}
