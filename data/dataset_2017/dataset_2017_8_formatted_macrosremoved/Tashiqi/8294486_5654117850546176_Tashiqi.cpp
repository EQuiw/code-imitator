#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
static const long long D = 1000000007;

int main() {
  long long T;
  cin >> T;
  for (long long t = 0; t < T; ++t) {
    long long n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    if (2 * max(max(r, y), b) > n)
      cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
    else {
      string s;
      int p = -1;
      if (r != 0) {
        --r;
        s += 'R';
        p = 0;
      } else if (b != 0) {
        --b;
        s += 'B';
        p = 1;
      }
      for (long long i = 0; i < n - 1; ++i) {
        if (r >= y and r >= b and p != 0) {
          --r;
          s += 'R';
          p = 0;
        } else if (b >= y and b >= r and p != 1) {
          --b;
          s += 'B';
          p = 1;
        } else if (y >= r and y >= b and p != 2) {
          --y;
          s += 'Y';
          p = 2;
        } else if ((r >= y or r >= b) and p != 0) {
          --r;
          s += 'R';
          p = 0;
        } else if ((b >= y or b >= r) and p != 1) {
          --b;
          s += 'B';
          p = 1;
        } else if ((y >= r or y >= b) and p != 2) {
          --y;
          s += 'Y';
          p = 2;
        } else
          cerr << "ERR" << endl;
      }
      cout << "Case #" << t + 1 << ": " << s << endl;
    }
  }
  return 0;
}
