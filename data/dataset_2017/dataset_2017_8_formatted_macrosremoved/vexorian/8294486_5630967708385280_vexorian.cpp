

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <unistd.h>
// http://gmplib.org/ (uncomment if solution uses big nums)
// most likely you'll get an error about mpz_class not being declared...
//#include "gmpxx.h"

// I figure that when other people want to test my solutions they shouldn't
// get the whole multi-threaded mess that requires and deletes folders and
// files...

typedef long long int64;

using namespace std;

//=========================================================
// program:
//
struct solver {
  int D, N;
  vector<int> K, S;

  double intersectPoint(double x0, double m0, double x1, double m1) {
    if (m0 == m1) {
      // they'll never cross
      return 1e100;
    }
    // x = x0 + y*m0
    // x = x1 + y*m1
    // 0 = (x0 - x1) + (m0 - m1)*y
    // y = (x1 - x0) / (m0 - m1)
    double y = (x1 - x0) / (m0 - m1);
    return x0 + y * m0;
  }
  bool validSpeed(double v) {
    for (int i = 0; i < N; i++) {
      double w = intersectPoint(0, v, K[i], S[i]);
      if (0.0 <= w && w < D) {
        // cout << "speed "<<v<<" is invalid for horse "<<i<<endl;
        // cout<< "w = "<<w<<endl;
        return false;
      }
    }
    return true;
  }

  double solve() {
    double lo = 0.0;  // P(lo) is true
    double hi = 1e30; // P(hi) is false
    for (int i = 0; i < 100000; i++) {
      double ha = (lo + hi) / 2;
      if (validSpeed(ha)) {
        lo = ha;
      } else {
        hi = ha;
      }
    }
    return lo;
  }
  void init() {}
  void read() {
    cin >> D >> N;
    K.resize(N);
    S.resize(N);
    for (int i = 0; i < N; i++) {
      cin >> K[i] >> S[i];
    }
  }

  void write(int cn) {
    double x = solve();
    cout << "Case #" << cn << ": ";
    cout.precision(10);
    cout.setf(ios::fixed, ios::fixed);
    cout << x << endl;
  }
};

//=========================================================
// I/O:
//
int main(int argc, const char *argv[]) {
  int TestCases, mode;

  // Simple and straight forward.
  cin >> TestCases;
  solver *theSolver = new solver;
  theSolver->init();
  for (int i = 1; i <= TestCases; i++) {
    theSolver->read();
    theSolver->write(i);
  }
  delete theSolver;
  return 0;
}
