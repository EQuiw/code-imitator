#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#include <fstream>
FILE *fin = freopen("a.in", "r", stdin);
FILE *fout = freopen("a.out", "w", stdout);

int main() {
  int T, t;
  long long n, k, m, r, b;
  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> n >> k;
    printf("Case #%d: ", t);
    for (b = 1; b * 2 <= k; b *= 2)
      ;
    n -= b;
    k -= b;
    m = n / b;
    r = n % b;
    if (k > r)
      m--;
    r = m / 2;
    m -= r;
    cout << m << " " << r << endl;
  }
  return 0;
}
