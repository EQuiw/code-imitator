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

int req[110], lb[110], ub[110];
int q[110][110];
int main() {

  freopen("input1.txt", "r", stdin);
  ;
  freopen("output_small.txt", "w", stdout);
  ;

  int n, i, j, k, l, m, t, s = 0, d, r, ans, p;
  scanf("%d", &t);
  ;
  int c = 1;
  while (t--) {
    memset((req), (0), sizeof(req));
    memset((lb), (0), sizeof(lb));
    memset((ub), (0), sizeof(ub));
    memset((q), (0), sizeof(q));
    scanf("%d", &n);
    ;
    scanf("%d", &p);
    ;
    for (i = 0; i < n; i++) {
      scanf("%d", &req[i]);
      ;
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < p; j++) {
        scanf("%d", &q[i][j]);
        ;
      }
    }
    for (i = 0; i < n; i++) {
      sort(q[i], q[i] + p);
    }
    for (i = 0; i < n; i++) {
      double nt = (9 * req[i]) / 10.0;
      lb[i] = (int)nt;
      if (lb[i] < nt)
        lb[i]++;
      ub[i] = (11 * req[i]) / 10;
    }
    int ns;
    ans = 0;
    bool vis[52][52];
    memset((vis), (0), sizeof(vis));
    // debugarr(q[1],2);
    for (i = 0; i < n; i++) {
      for (j = 0; j < p; j++) {
        if (q[i][j] < lb[i])
          continue;
        ns = q[i][j] / lb[i];
        int mx = q[i][j] / ub[i];
        if (mx * ub[i] < q[i][j]) {
          mx++;
        }
        swap(mx, ns);
        while (ns <= mx) {
          bool f = 1;
          // cout<<ns<<' '<<ns*lb[i]<<' '<<q[i][j]<<' '<<ns*ub[i]<<endl;;
          vector<pair<int, int>> v;
          v.clear();
          for (int m = i + 1; m < n; m++) {
            f = 0;
            for (int o = 0; o < p; o++) {
              // cout<<m<<' '<<o<<' '<<ns<<' '<<ns*lb[m]<<' '<<q[m][o]<<'
              // '<<ns*ub[m]<<' '<<vis[m][o]<<endl;;
              if (!vis[m][o] && ns * lb[m] <= q[m][o] &&
                  ns * ub[m] >= q[m][o]) {
                vis[m][o] = true;
                v.push_back(make_pair(m, o));
                f = 1;
                break;
              }
            }
            // cout<<f<<endl;
            if (f == 0)
              break;
          }
          if (f == 0) {
            for (int o = 0; o < v.size(); o++) {
              vis[v[o].first][v[o].second] = false;
            }
          } else {
            ans++;

            break;
          }
          ns++;
        }
      }
      break;
    }
    printf("Case #%d: %d\n", c++, ans);
  }
  return (0);
}
