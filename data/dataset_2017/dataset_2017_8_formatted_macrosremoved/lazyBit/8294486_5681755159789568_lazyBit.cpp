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
const char colors[] = {'R', 'O', 'Y', 'G', 'B', 'V'};
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

double besttime[1010];
LL c[110], d[110], dist[110][110], a[110], b[110], dd[110];
long double best[110][110];
int main() {

  freopen("input.txt", "r", stdin);
  ;
  // output;

  long long n, k, l, m, t, s = 0, p, q;
  int i, j;
  cin >> t;
  int ct = 1;
  while (t--) {
    scanf("%lld", &n);
    ;
    scanf("%lld", &q);
    ;
    for (i = 0; i < n; i++) {
      scanf("%lld", &c[i]);
      ;
      scanf("%lld", &d[i]);
      ;
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        scanf("%lld", &dist[i][j]);
        ;
      }
    }
    for (i = 0; i < q; i++) {
      scanf("%lld", &a[i]);
      ;
      scanf("%lld", &b[i]);
      ;
    }
    dd[0] = 0;
    for (i = 1; i < n; i++) {
      dd[i] = dd[i - 1] + dist[i - 1][i];
    }
    besttime[0] = 0.0;
    long double r;
    for (i = 1; i < n; i++) {
      r = 1e18;
      for (j = 0; j < i; j++) {
        if (dd[i] - dd[j] <= c[j]) {
          best[i][j] = besttime[j] + ((dd[i] - dd[j]) * 1.0) / d[j];
        } else {
          best[i][j] = 1e18;
        }
        r = min(r, best[i][j]);
      }
      besttime[i] = r;
    }
    // if(besttime[n-1]<0) {
    // 	cerr<<n<<' '<<q<<endl;
    // }
    printf("Case #%d: %0.6lf\n", ct++, besttime[n - 1]);
  }
  return (0);
}
