

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
  string S;
  int K;

  int solve() {
    int cost = 0;
    for (int i = 0; i + K <= S.size(); i++) {
      if (S[i] != '+') {
        cost++;
        // flip
        for (int j = i; j < i + K; j++) {
          S[j] = ((S[j] == '+') ? '-' : '+');
        }
      }
    }
    for (int i = S.size() - K; i < S.size(); i++) {
      if (S[i] != '+') {
        return -1;
      }
    }
    return cost;
  }

  void init() {}
  void read() { cin >> S >> K; }

  void write(int cn) {
    cout << "Case #" << cn << ": ";
    int s = solve();
    if (s == -1) {
      cout << "IMPOSSIBLE";
    } else {
      cout << s;
    }
    cout << endl;
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
