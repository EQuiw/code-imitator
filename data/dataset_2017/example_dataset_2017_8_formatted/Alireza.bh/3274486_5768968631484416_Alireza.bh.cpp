#define _CRT_SECURE_NO_WARNINGS
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
#define FR(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FOR(i, c, n) for (int(i) = (c); (i) < (n); (i)++)
#define REP(it, v, cont)                                                       \
  for (cont::iterator(it) = (v).begin(); (it) != (v).end(); ++(it))
#define CLR(a, c) memset((a), (c), sizeof(a))
#define ALL(v) (v).begin(), (v).end()
#define SQR(a) ((a) * (a))
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

double memo[1100][1100][3];
vector<PLL> v;
double inf = 1e100;
double pi = 4 * atan(1.);
double f(int ind, int k, bool usedbefore) {
  if (k < 0)
    return -inf;
  if (ind == v.size()) {
    if (k == 0)
      return 0;
    return -inf;
  }
  double maxi = -inf;
  double &ret = memo[ind][k][usedbefore];
  if (ret > -0.5)
    return ret;
  double extera = usedbefore ? 0 : (pi * v[ind].first * v[ind].first);

  maxi = max(f(ind + 1, k, usedbefore),
             extera + 2 * pi * v[ind].first * v[ind].second +
                 f(ind + 1, k - 1, true));
  return ret = maxi;
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcase;
  cin >> Tcase;
  FR(cas, Tcase) {
    printf("Case #%d: ", cas + 1);
    int n, k;
    cin >> n >> k;

    v.clear();
    FR(i, n) {
      PLL p;
      cin >> p.first >> p.second;
      v.push_back(p);
    }
    sort(ALL(v));
    reverse(ALL(v));
    CLR(memo, -1);
    cout << fixed << setprecision(9) << f(0, k, false) << endl;
  }
}