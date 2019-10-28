

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
  int N, Q;
  vector<int> E, S;
  int D[101][101];
  int U[101];
  int V[101];

  double solve() {
    assert(U[0] == 1);
    assert(V[0] == N);
    assert(Q == 1);

    // from city 0 to N-1 ...
    double dp[100][100];
    for (int i = 0; i < N; i++) {
      dp[N - 1][i] = 0.0;
    }
    for (int j = N - 2; j >= 0; j--) {
      for (int h = 0; h <= j; h++) {
        int64 traveled = 0;
        for (int i = h; i < j; i++) {
          traveled += D[i][i + 1];
        }
        dp[j][h] = dp[j + 1][j] + D[j][j + 1] / (double)S[j]; // switch horse
        // keep the horse
        if (traveled + D[j][j + 1] <= E[h]) {
          dp[j][h] =
              std::min(dp[j][h], D[j][j + 1] / (double)S[h] + dp[j + 1][h]);
        }
      }
    }
    return dp[0][0];
  }
  void init() {}
  void read() {
    cin >> N >> Q;
    E.resize(N);
    S.resize(N);
    for (int i = 0; i < N; i++) {
      cin >> E[i] >> S[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> D[i][j];
      }
    }
    for (int i = 0; i < Q; i++) {
      cin >> U[i] >> V[i];
    }
  }

  void write(int cn) {
    double r = solve();
    cout << "Case #" << cn << ": ";
    cout.precision(10);
    cout.setf(ios::fixed, ios::fixed);
    cout << r << endl;
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
