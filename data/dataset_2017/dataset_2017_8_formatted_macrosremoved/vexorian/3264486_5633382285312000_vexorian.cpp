

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
  string N;
  int64 mem[20][10][2];
  int64 pow10[21];
  int64 rec(int p, int last, int eq) {
    int64 &res = mem[p][last][eq];
    if (res == -1) {
      res = -2;
      if (p == N.size()) {
        // welp
        res = 0;
      } else {
        for (int d = last; d <= 9; d++) {
          if (!eq || (d <= N[p] - '0')) {
            int neq = (eq && ((N[p] - '0') == d));
            int nlast = d;
            int64 x = rec(p + 1, nlast, neq);
            if (x != -2) {
              x = d * pow10[N.size() - p - 1] + x;
              res = std::max(res, x);
            }
          }
        }
      }
    }
    return res;
  }

  int64 solve() {
    memset(mem, -1, sizeof(mem));
    pow10[0] = 1;
    for (int i = 1; i < N.size(); i++) {
      pow10[i] = pow10[i - 1] * 10;
    }
    return rec(0, 0, 1);
  }

  void init() {}

  void read() { cin >> N; }

  void write(int cn) { cout << "Case #" << cn << ": " << solve() << endl; }
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
