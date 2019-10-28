#include <bitset>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>

#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include <numeric>
#include <utility>
#include <vector>
// #include <random>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;

typedef long long LL;           // NOTES:int64
typedef unsigned long long ULL; // NOTES:uint64
typedef unsigned uint;

const double pi = acos(-1.0); // NOTES:pi
const double eps = 1e-11;     // NOTES:eps
const int MAXI = 0x7fffffff;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
const char dz[] = "SENW";
struct debugger {
  template <typename T> debugger &operator,(const T &v) {
    cerr << v << " ";
    return *this;
  }
} dbg;

void debugarr(int *arr, int n) {
  cout << "[";
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  cout << "]" << endl;
}

int main() {

  freopen("input.txt", "r", stdin);
  ;
  // output;

  int n, i, j, k, l, m, t, s = 0, d, p;
  scanf("%d", &t);
  ;
  int c = 1;
  while (t--) {
    scanf("%d", &d);
    ;
    scanf("%d", &n);
    ;
    double ans = 0.0;
    double r;
    // cout<<n<<endl;
    for (i = 0; i < n; i++) {
      scanf("%d", &k);
      ;
      scanf("%d", &s);
      ;
      double r = ((d - k) * 1.0) / s;
      // cout<<k<<' '<<s<<' '<<r<<endl;
      ans = max(ans, r);
    }
    printf("Case #%d: %0.6lf\n", c++, d / ans);
  }
  return (0);
}
