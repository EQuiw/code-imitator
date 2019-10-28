

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
  template <class A, class B> void fill_thing(A &collection, B default_value) {
    B p = default_value;
    for (int i = 0; i < collection.size(); i++) {
      if (collection[i] != default_value) {
        p = collection[i];
      } else {
        collection[i] = p;
      }
    }
    p = default_value;
    for (int i = collection.size() - 1; i >= 0; i--) {
      if (collection[i] != default_value) {
        p = collection[i];
      } else {
        collection[i] = p;
      }
    }
  }

  vector<string> solve(vector<string> board) {
    int n = board.size(), m = board[0].size();
    for (string &row : board) {
      if (count(row.begin(), row.end(), '?') < m) {
        fill_thing(row, '?');
      }
    }
    fill_thing(board, string(m, '?'));
    return board;
  }
  void init() {}
  vector<string> board;
  void read() {
    int R, C;
    cin >> R >> C;
    board = vector<string>(R, string(C, '?'));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        cin >> board[i][j];
      }
    }
  }

  void write(int cn) {
    cout << "Case #" << cn << ":" << endl;
    auto v = solve(board);
    for (string &s : v) {
      cout << s << endl;
    }
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
