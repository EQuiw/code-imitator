#ifdef VX_PRECOMPILED
#include "precomp.h"
typedef mpz_class big;
// I use 4 cores :)
#define MAX_THREADS 4
#else
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <unistd.h>
// http://gmplib.org/ (uncomment if solution uses big nums)
// most likely you'll get an error about mpz_class not being declared...
//#include "gmpxx.h"
#define big mpz_class
// I figure that when other people want to test my solutions they shouldn't
// get the whole multi-threaded mess that requires and deletes folders and
// files...
#define MAX_THREADS 1
#endif

#define for_each(q, s) for (typeof(s.begin()) q = s.begin(); q != s.end(); q++)
typedef long long int64;
#define long int64

using namespace std;

//=========================================================
// program:
//
struct solver {
  int N, P;
  int R[51];
  int Q[51][51];

  tuple<int, int> get_min_max_servings(int r, int q) {
    // r units required for a serving
    // q in a package.
    int min_s = 2000000000, max_s = -1;
    for (int s = 1; s <= 10000000; s++) {
      // 10000000000000
      long rr = r * (long)s;
      // is:   ( 0.9 rr <= q <= 1.1 rr) ?
      // (0.9 rr <= q)
      // (9 * rr <= q * 10)

      // (q <= 1.1 rr)
      // (10q <= 11)
      if (9 * rr <= 10 * q && 10 * q <= 11 * rr) {
        min_s = std::min(min_s, s);
        max_s = std::max(max_s, s);
      }
    }
    return make_tuple(min_s, max_s);
  }

  int min_s[51][51];
  int max_s[51][51];

  int solve1() {
    int c = 0;
    for (int i = 0; i < P; i++) {
      if (min_s[0][i] <= max_s[0][i]) {
        c++;
      }
    }
    return c;
  }

  bool intersect(int a, int b, int c, int d) {

    // do intervals [a,b] and [c,d] intersect?
    if (a <= c && c <= b) {
      return true;
    }
    if (c <= b && b <= d) {
      return true;
    }
    // sixth mistake : forgetting these other cases:
    if (a <= d && d <= b) {
      return true;
    }
    if (c <= a && a <= d) {
      return true;
    }

    return false;
  }

  int solve2() {
    int dp[1 << P];
    dp[0] = 0;
    for (int mask = 1; mask < (1 << P); mask++) {
      int i = P - __builtin_popcount(mask);
      // match package #i of first product with something available
      dp[mask] = 0;
      for (int j = 0; j < P; j++) {
        if (mask & (1 << j)) {
          dp[mask] = std::max(dp[mask], dp[mask ^ (1 << j)]);
        }
      }

      for (int j = 0; j < P; j++) {
        if (mask & (1 << j)) {
          // third mistake, forgot to move this inside the else .-.
          if (intersect(min_s[0][i], max_s[0][i], min_s[1][j], max_s[1][j])) {
            dp[mask] = std::max(dp[mask], 1 + dp[mask ^ (1 << j)]);
          }
        }
      }
      // cout << "dp["<<mask<<"] = "<<dp[mask]<<endl;
    }
    return dp[(1 << P) - 1];
  }

  int solve() {
    assert(N <= 2);
    for (int i = 0; i < N; i++) {
      // cout << i << ":"<<endl;
      for (int j = 0; j < P; j++) {
        tie(min_s[i][j], max_s[i][j]) = get_min_max_servings(R[i], Q[i][j]);
        // cout << " " << min_s[i][j] << " " << max_s[i][j]<< endl;
      }
    }

    if (N == 1) {
      // "simple"...
      return solve1();
    } else {
      return solve2();
    }
  }
  void init() {}
  void read() {
    cin >> N >> P;
    for (int i = 0; i < N; i++) {
      cin >> R[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        cin >> Q[i][j];
      }
    }
  }
#if MAX_THREADS > 1
  ofstream cout;
#endif
  void write(int cn) {
    int x = solve();
    cout << "Case #" << cn << ": " << x << endl;
  }
};

//=========================================================
// I/O:
//
#if MAX_THREADS > 1
void run(const char *x) {
  int r = system(x);
  cerr << x << " "
       << "(" << r << ")" << endl;
}
#endif

int main(int argc, const char *argv[]) {
  int TestCases, mode;
#if MAX_THREADS == 1
  // Simple and straight forward.
  cin >> TestCases;
  solver *theSolver = new solver;
  theSolver->init();
  for (int i = 1; i <= TestCases; i++) {
    theSolver->read();
    theSolver->write(i);
  }
  delete theSolver;
#else
  cin >> TestCases;
  //-------------------------------------------
  // Copy the whole input to a file...
  ofstream f;
  f.open("tests/.input");
  f << cin.rdbuf();
  f.close();
  // Yeah...wipe that folder... Cause we will need its files to be empty
  run("rm ./tests/.t*");
  int k = 0;
  mode = 0;
  // We create some extra threads...
  while (k < MAX_THREADS) {
    if (fork() == 0) {
      mode = k + 1;
      break;
    }
    k++;
  }
  // Reopen the input, this happens for each of the threads...
  if (mode != 0) {
    assert(freopen("tests/.input", "r", stdin));
  }

  solver *theSolver = new solver;
  theSolver->init();
  for (int i = 1; i <= TestCases; i++) {
    // Yeah, I don't like this much either
    ofstream f;
    char fn1[200], fn2[200];
    sprintf(fn1, "tests/.test.%d", i);
    sprintf(fn2, "tests/.test.%d.done", i);
    if (mode == 0) {
      // main thread shall just join stuff together as it becomes ready
      struct stat stFileInfo;
      // When a thread finishes a test case, it writes the .done file
      // Wait for that...
      while (stat(fn2, &stFileInfo) != 0) {
        sleep(1);
      }
      // Now copy the output file...
      ifstream f(fn1);
      cout << f.rdbuf();
    } else {
      // The trick is to make each thread read all the inputs, whether
      // it will process it or not...
      theSolver->read();
      // If fn1 exists, it is being processed already. Else process it
      f.open(fn1, ios_base::out | ios_base::in);
      if (!f) {
        theSolver->cout.open(fn1, ios_base::out);
        cerr << "[" << i << "/" << TestCases << "] " << mode << endl;
        theSolver->write(i);
        theSolver->cout.close();
        f.open(fn2);
        f << "1" << endl;
      }
    }
  }
  delete theSolver;
#endif

  return 0;
}
