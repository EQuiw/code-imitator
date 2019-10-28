#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  freopen("C.in", "r", stdin);
  freopen("C.txt", "w", stdout);
  int t, r, rr;
  long long n, k, m, L, R, nn, total;
  cin >> t;
  for (int aa = 0; aa < t; aa++) {
    r = 0;
    rr = 0;
    cin >> n >> k;
    m = k;
    nn = n;
    while (nn > 1) {
      rr++;
      nn /= 2ll;
    }
    while (m > 1) {
      r++;
      m /= 2ll;
    }

    long long poww = 1ll;
    for (int i = 0; i < r; i++)
      poww = poww * 2ll;
    poww = poww * 2ll - 1;
    // cout << "---" << poww << endl;
    if (n <= poww) {
      L = 0;
      R = 0;
    } else {
      long long pp = 1ll;
      for (int i = 0; i < r; i++)
        pp = pp * 2ll;
      long long left = n - pp * 2ll + 1;
      long long res = left % pp;
      long long qq = left / pp;
      // cout << "++++ " << r << " " << pp << " " << left << " " << res << " "
      // << qq << endl;
      if (res >= k - pp + 1) {
        long long h = (qq + 1ll) / 2ll;
        L = qq + 1 - h;
        R = h;
      } else {
        L = qq - (qq) / 2ll;
        R = qq / 2ll;
      }
    }

    // if(m * 2ll <= n) {
    // 	m = m * 2ll;
    // 	while(m * 2ll <= n) {
    // 		r++;
    // 		m = m * 2ll;
    // 	}
    // 	long long pp = 1ll;
    // 	for(int i=0;i<r;i++) pp = pp * 2ll;
    // 	cout << "====" << m << " " << pp << " " << n << endl;
    // 	if(m + pp < n) {
    // 		// all
    // 		L = pp * 2ll - 1;
    // 	}
    // 	else {
    // 		L = n - m + 1 + pp -1;
    // 	}
    // } else {
    // 	L = 0;
    // }

    cout << "Case #" << aa + 1 << ": " << L << " " << R << endl;
  }
}
