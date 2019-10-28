

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
  pair<int64, int64> solve(int64 N, int64 K) {
    map<int64, int64> count;
    count[N] = 1;
    set<int64, greater<int64>> Q;
    Q.insert(N);
    while (!Q.empty()) {
      auto it = Q.begin();
      int64 x = *it;
      int64 c = count[x];
      // cout << K << " : " << x << " : " << c << endl;
      Q.erase(x);

      int64 a = (x - 1) / 2;
      int64 b = x - 1 - a;
      if (K <= c) {
        return {b, a};
      }
      // cout << "a="<<a<<" , b="<<b<<endl;
      K -= c;
      count[a] += c;
      count[b] += c;
      Q.insert(a);
      Q.insert(b);
    }
    cout << "K = " << K << endl;
    assert(false);
    return {-1, -1};
  }
  void init() {}
  int64 N, K;
  void read() { cin >> N >> K; }

  void write(int cn) {
    cout << "Case #" << cn << ": ";
    auto x = solve(N, K);
    cout << x.first << " " << x.second << endl;
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
