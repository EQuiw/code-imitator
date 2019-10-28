#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int tt;

  cin >> tt;

  for (int t = 1; t <= tt; ++t) {
    int d, n;
    cin >> d >> n;

    long long bk, bs, k, s;
    cin >> k >> s;
    k = d - k;
    bk = k;
    bs = s;
    for (int i = 1; i < n; ++i) {
      cin >> k >> s;
      k = d - k;
      if (s * bk < bs * k) {
        bs = s;
        bk = k;
      }
    }
    bs *= d;
    long long q = bs / bk, r = bs % bk;

    cout << "Case #" << t << ": " << q << ".";
    for (int i = 0; i < 6; ++i) {
      r = r * 10;
      cout << r / k;
      r = r % k;
    }
    cout << endl;
  }

  return 0;
}
