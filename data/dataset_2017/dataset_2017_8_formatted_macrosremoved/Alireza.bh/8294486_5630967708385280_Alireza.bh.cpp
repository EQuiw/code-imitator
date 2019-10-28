
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
    int D, N;
    cin >> D >> N;
    vector<PII> v;
    for (int(i) = 0; (i) < (N); (i)++) {
      PII p;
      cin >> p.first >> p.second;
      v.push_back(p);
    }
    sort((v).begin(), (v).end());
    reverse((v).begin(), (v).end());
    double res = 0;
    for (int(i) = 0; (i) < (N); (i)++)
      res = max(res, ((double)D - v[i].first) / v[i].second);
    cout << fixed << setprecision(9) << D / res << endl;
  }
}
