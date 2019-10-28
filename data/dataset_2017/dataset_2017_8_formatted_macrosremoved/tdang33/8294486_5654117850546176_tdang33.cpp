#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

void solve(long long n, long long r, long long o, long long y, long long g,
           long long b, long long v) {
  string s = "";
  long long m = max(r, y);
  m = max(m, b);
  if (m > r + y + b - m) {
    cout << "IMPOSSIBLE";
  } else {

    long long d = r + y + b - m - m;
    char a, b, c;
    long long w, z;
    if (m == r) {
      w = y;
      z = b;
      a = 'R';
      b = 'Y';
      c = 'B';
    } else if (m == y) {
      w = r;
      z = b;
      a = 'Y';
      b = 'R';
      c = 'B';
    } else {
      w = r;
      z = y;
      a = 'B';
      b = 'R';
      c = 'Y';
    }
    for (int i = 0; i < m; i++) {
      if (i < w - d) {
        s += a;
        s += b;
      } else if (i < w + z - 2 * d) {
        s += a;
        s += c;
      } else {
        s += a;
        s += b;
        s += c;
      }
    }
    cout << s;
  }
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    long long n;
    cin >> n;
    long long r, o, y, g, b, v;
    cin >> r >> o >> y >> g >> b >> v;
    cout << "Case #" << i + 1 << ": ";
    solve(n, r, o, y, g, b, v);
    cout << endl;
  }
  return 0;
}
