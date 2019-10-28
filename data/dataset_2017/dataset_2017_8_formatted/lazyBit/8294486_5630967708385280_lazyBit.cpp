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

#define rep(i, n) for (int i = 0; i < n; i++)
#define loop(i, a, b) for (int i = (a), _b = (b); i < _b; i++)
#define rloop(i, b, a) for (int i = (b)-1, _a = (a); i >= _a; i--)
#define Reset(a, b) memset((a), (b), sizeof(a))

#define endline putchar('\n')
#define space putchar(' ')
#define EXIT(x)                                                                \
  {                                                                            \
    cout << x;                                                                 \
    return 0;                                                                  \
  }

#define fi first
#define se second
#define pb push_back

#define S(x) scanf("%d", &x);
#define input freopen("input.txt", "r", stdin);
#define output freopen("output_small.txt", "w", stdout);
#define deb(i, a, n)                                                           \
  for (i = 0; i < n; i++) {                                                    \
    cout << a[i] << " ";                                                       \
  }
#define db(x, y) printf("%d %d\n", x, y);
#define debug(args...)                                                         \
  {                                                                            \
    dbg, args;                                                                 \
    cerr << endl;                                                              \
  }
#define dline cerr << endl
#define INF (int)1e9
#define LINF (long long)1e18
#define EPS 1e-9
#define maX(a, b) ((a) > (b) ? (a) : (b))
#define miN(a, b) ((a) < (b) ? (a) : (b))
#define abS(x) ((x) < 0 ? -(x) : (x))
#define mod 1000000007

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
#ifndef ONLINE_JUDGE
  input;
  // output;
#endif
  int n, i, j, k, l, m, t, s = 0, d, p;
  S(t);
  int c = 1;
  while (t--) {
    S(d);
    S(n);
    double ans = 0.0;
    double r;
    // cout<<n<<endl;
    for (i = 0; i < n; i++) {
      S(k);
      S(s);
      double r = ((d - k) * 1.0) / s;
      // cout<<k<<' '<<s<<' '<<r<<endl;
      ans = max(ans, r);
    }
    printf("Case #%d: %0.6lf\n", c++, d / ans);
  }
  return (0);
}
