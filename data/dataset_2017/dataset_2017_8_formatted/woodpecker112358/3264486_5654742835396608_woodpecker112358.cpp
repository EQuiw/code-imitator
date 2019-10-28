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

struct seg {
  mint len;
  mint lft;
  seg(mint lenn, mint lftt) : len(lenn), lft(lftt) {}
  bool operator<(const seg &a) const {
    return (len == a.len) ? (lft < a.lft) : (len < a.len);
  }
};
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("cout.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    mint n, k;
    cin >> n >> k;
    priority_queue<seg> pq;
    pq.push(seg(n, 0));
    mint mxl = numeric_limits<mint>::min(), mnl = numeric_limits<mint>::max();
    while (k--) {
      seg top = pq.top();
      pq.pop();
      mint lft = top.lft;
      mint len = top.len;
      mint mid = lft + (len - 1) / 2;
      mint lfl = mid - lft;
      mint rgl = lft + len - 1 - mid;
      if (lfl) {
        pq.push(seg(lfl, lft));
      }
      if (rgl) {
        pq.push(seg(rgl, mid + 1));
      }
      mxl = rgl;
      mnl = lfl;
    }
    cout << "Case #" << t << ": " << mxl << " " << mnl << endl;
  }
  return 0;
}
