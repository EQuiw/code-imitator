
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
  int Tcase;
  cin >> Tcase;
  for (int(cas) = 0; (cas) < (Tcase); (cas)++) {
    printf("Case #%d: ", cas + 1);
    int n, k;
    cin >> n >> k;
    double u;
    cin >> u;
    vector<double> v;
    for (int(i) = 0; (i) < (n); (i)++) {
      double temp;
      cin >> temp;
      v.push_back(temp);
    }
    sort((v).begin(), (v).end());
    double res = 0;
    for (int(i) = 0; (i) < (v.size()); (i)++) {
      double sum = 0;
      for (int(j) = 0; (j) < (i + 1); (j)++)
        sum += v[i] - v[j];
      if (sum > u)
        continue;
      double maxiBound = v[i] + (u - sum) / (i + 1);
      maxiBound = min(maxiBound, 1.);
      sum = 1;
      for (int(j) = 0; (j) < (i + 1); (j)++)
        sum *= maxiBound;
      for (int(j) = (i + 1); (j) < (v.size()); (j)++)
        sum *= v[j];
      res = max(res, sum);
    }
    cout << fixed << setprecision(9) << res << endl;
  }
}
