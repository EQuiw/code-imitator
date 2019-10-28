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

char str[50][50];
bool vis[50][50];
int main() {
  // #ifndef ONLINE_JUDGE
  //        input;
  //        output;
  //    #endif
  int n, i, j, k, l, m, t, s = 0, d, r;
  scanf("%d", &t);
  ;
  int c = 1;
  while (t--) {
    scanf("%d", &r);
    ;
    scanf("%d", &l);
    ;
    memset((vis), (0), sizeof(vis));
    for (i = 0; i < r; i++) {
      cin >> str[i];
    }
    for (i = 0; i < r; i++) {
      for (j = 0; j < l; j++) {
        if (str[i][j] != '?' && !vis[i][j]) {
          k = i - 1;
          while (k >= 0 && str[k][j] == '?') {
            str[k][j] = str[i][j];
            vis[k][j] = true;
            k--;
          }
          k = i + 1;
          while (k < r && str[k][j] == '?') {
            str[k][j] = str[i][j];
            vis[k][j] = true;
            k++;
          }
        }
      }
    }

    memset((vis), (0), sizeof(vis));
    for (i = 0; i < r; i++) {
      for (j = 0; j < l; j++) {
        if (str[i][j] != '?' && !vis[i][j]) {
          k = j - 1;
          while (k >= 0 && str[i][k] == '?') {
            str[i][k] = str[i][j];
            vis[i][k] = true;
            k--;
          }
          k = j + 1;
          while (k < l && str[i][k] == '?') {
            str[i][k] = str[i][j];
            vis[i][k] = true;
            k++;
          }
        }
      }
    }
    printf("Case #%d:\n", c++);
    for (i = 0; i < r; i++) {
      cout << str[i] << endl;
    }
  }
  return (0);
}
