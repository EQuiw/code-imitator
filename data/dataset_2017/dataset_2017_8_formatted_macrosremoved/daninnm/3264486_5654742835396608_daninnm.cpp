#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int maxt;
unsigned long long n, k;
int main() {
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
  cin >> maxt;
  for (int tr = 1; tr <= maxt; ++tr) {
    cin >> n >> k;
    unsigned long long t = 0;
    while (t < k) {
      t = t * 2 + 1;
    }
    t = t / 2;
    k -= t;
    n -= t;
    unsigned long long a, r, ans;
    a = n % (t + 1);

    if (k > a) {
      r = n / (t + 1) - 1;
    } else {
      r = n / (t + 1);
    }
    cout << "Case #" << tr << ": ";
    cout << (r + 1) / 2 << " " << r / 2;
    cout << endl;
  }
  return 0;
}
