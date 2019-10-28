#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#define PI (acos(-1.0))
#define Abs(a) (((a) < 0) ? (-(a)) : (a))
#define rep(i, n) for ((i) = 0; (i) < (n); (i)++)
#define Rep(i, n) for (int i = 0; i < (n); i++)
#define Rrep(i, n) for (int i = ((n)-1); i >= 0; i--)
#define rrep(i, n) for ((i) = (n)-1; (i) >= 0; (i)--)
#define Pii pair<int, int>
#define PB push_back
#define Size(x) ((int)(x.size()))
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("Bout.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    printf("Case #%d: ", t);
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    vector<pair<int, char>> vv(3);
    vv[0] = make_pair(r, 'R');
    vv[1] = make_pair(y, 'Y');
    vv[2] = make_pair(b, 'B');
    sort(vv.begin(), vv.end(), greater<pair<int, char>>());
    if (vv[0].first > vv[1].first + vv[2].first) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      list<char> l;
      int ext = vv[0].first - vv[2].first - (vv[1].first - vv[2].first);
      while (vv[2].first) {
        l.PB(vv[0].second);
        l.PB(vv[1].second);
        if (ext) {
          l.PB(vv[0].second);
          ext--;
        }
        l.PB(vv[2].second);
        vv[0].first--;
        vv[1].first--;
        vv[2].first--;
      }
      while (vv[1].first) {
        l.PB(vv[0].second);
        l.PB(vv[1].second);
        vv[0].first--;
        vv[1].first--;
      }
      for (auto it = l.begin(); it != l.end(); it++) {
        printf("%c", *it);
      }
      cout << endl;
    }
  }
  return 0;
}
