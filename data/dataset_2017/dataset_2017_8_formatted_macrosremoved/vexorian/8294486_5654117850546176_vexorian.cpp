

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
const int MAX = 1001;
struct solver {
  int N;
  int R, O, Y, G, B, V;
  char mem[3][MAX][MAX][MAX]; // we got the RAMs
  char s;

  bool rec(int last, int A, int B, int C) {
    if ((A < 0) || (B < 0) || (C < 0)) {
      return 0;
    }
    char &res = mem[last][A][B][C];
    if (res == -1) {
      res = 0;
      int p = N - (A + B + C);
      if (p == N) {
        // picked all of them
        res = 1;
      } else {
        for (int i = 0; i < 3; i++) {
          if ((i != last) && ((p != N - 1) || (i != s))) {
            if (rec(i, A - (i == 0), B - (i == 1), C - (i == 2))) {
              res = 1;
            }
          }
        }
      }
    }
    return res;
  }
  string solve() {
    assert(O == 0);
    assert(G == 0);
    assert(V == 0);
    if (R != 0) {
      R--;
      s = 0;
    } else if (Y != 0) {
      Y--;
      s = 2;
    } else if (B != 0) {
      B--;
      s = 1;
    }
    memset(mem, -1, sizeof(mem));
    if (rec(s, R, B, Y)) {
      // build it
      string res(N, '?');
      const string chars = "RBY";
      res[0] = chars[s];
      int last = s;
      int A = R, C = Y;
      for (int p = 1; p < N; p++) {
        for (int i = 0; i < 3; i++) {
          if ((i != last) && ((p != N - 1) || (i != s))) {
            // try it
            if (rec(i, A - (i == 0), B - (i == 1), C - (i == 2))) {
              // a valid one
              res[p] = chars[i];
              last = i;
              A -= (i == 0);
              B -= (i == 1);
              C -= (i == 2);
              break;
            }
          }
        }
        assert(res[p] != '?');
      }
      return res;
    } else {
      return "IMPOSSIBLE";
    }
  }
  void init() {}
  void read() { cin >> N >> R >> O >> Y >> G >> B >> V; }

  void write(int cn) {
    string s = solve();
    cout << "Case #" << cn << ": " << s << endl;
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
