#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 9;
vii v;
int d, n;
ld simula() {
  ld taux = 0;
  for (ii x : v) {
    ld t2 = (d - x.first) / (double)x.second;
    taux = max(t2, taux);
  }
  return d / taux;
}
ld solve() {
  scanf("%d%d", &d, &n);
  v.clear();
  for (int i = 0; i < n; i++) {
    int k, d;
    scanf("%d%d", &k, &d);
    v.push_back(make_pair(k, d));
  }
  return simula();
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    cout << fixed << setprecision(6);
    cout << solve() << endl;
  }
  return 0;
}
