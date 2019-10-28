#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

const long double inf = 1e18 + 7;

const long double eps = 1e-18;

void fail(int tt) { cout << "Case #" << tt + 1 << ": IMPOSSIBLE\n"; }

void ok(string ans, int tt) {
  cout << "Case #" << tt + 1 << ": " << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);

  int t;
  cin >> t;
  for (int tt = 0; tt < t; ++tt) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    int rr = R;
    int yy = Y;
    int bb = B;
    string ans;
    char cr = 'R';
    char cb = 'B';
    char cy = 'Y';
    if (Y >= R && Y >= B) {
      cr = 'Y', cb = 'B', cy = 'R';
      swap(Y, R);
    } else if (B >= R && B >= Y) {
      cr = 'B', cb = 'R', cy = 'Y';
      swap(B, R);
    }
    string buf(R, cr);
    for (int i = 0; i < Y; ++i)
      ans.push_back(buf.back()), ans.push_back(cy), buf.pop_back();
    ans = ans + buf;
    buf = ans;
    ans = "";
    for (int i = 0; i < B; ++i)
      ans.push_back(cb), ans.push_back(buf.back()), buf.pop_back();
    while (buf.size())
      ans.push_back(buf.back()), buf.pop_back();

    bool okfl = 1;
    for (int i = 0; i < ans.size(); ++i)
      if (ans[i] == ans[(i + 1) % ans.size()]) {
        fail(tt), okfl = 0;
        break;
      }

    for (auto x : ans) {
      if (x == 'R')
        --rr;
      if (x == 'Y')
        --yy;
      if (x == 'B')
        --bb;
    }
    if (rr != 0)
      assert(0);
    if (bb != 0)
      assert(0);
    if (yy != 0)
      assert(0);
    if (okfl) {
      ok(ans, tt);
    }
  }
  return 0;
}
