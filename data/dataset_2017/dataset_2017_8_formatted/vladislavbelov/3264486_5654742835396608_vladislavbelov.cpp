/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main() {
  ios::sync_with_stdio(false);
#ifdef HOME
  freopen("C.in", "rt", stdin);
  freopen("C.out", "wt", stdout);
  clock_t start = clock();
#endif
  solution();
#ifdef HOME
  cerr << "Total time: " << fixed << setprecision(3)
       << double(clock() - start) / double(CLOCKS_PER_SEC) << endl;
#endif
  return EXIT_SUCCESS;
}

typedef long long ll;
#define int ll

pair<int, int> solve_naive(int n, int k) {
  vector<char> u(n + 2);
  u[0] = u[n + 1] = 1;
  int last_ls = -1, last_rs = -1;
  for (int i = 0; i < k; ++i) {
    int index = -1, dist = -1, dist_max = -1;
    for (int i = 1; i <= n; ++i) {
      if (u[i])
        continue;
      int ls = i, rs = i;
      while (!u[ls])
        --ls;
      while (!u[rs])
        ++rs;
      int d_min = min(i - ls, rs - i);
      int d_max = max(i - ls, rs - i);
      if (index == -1 || dist < d_min || (dist == d_min && dist_max < d_max)) {
        dist = d_min;
        dist_max = d_max;
        index = i;
        last_ls = i - ls - 1;
        last_rs = rs - i - 1;
      }
    }
    u[index] = 1;
  }
  return make_pair(max(last_ls, last_rs), min(last_ls, last_rs));
}

int power(int n) {
  for (int i = 1;; i *= 2)
    if (i > n)
      return i;
  return 0;
}

pair<int, int> solve(int n, int k) {
  int first = 0, second = 0;
  int pwr = power(k);
  int m = k - pwr / 2;
  first = (n - m) / pwr;
  second = (n - k) / pwr;
  return make_pair(first, second);
}

void solution() {
  /*
  const int N = 500;
  cout << "   k:  | ";
  for (int k = 1; k <= N; ++k)
      cout << setw(4) << k << "    |";
  cout << endl;
  cout << "-------+-";
  for (int k = 1; k <= N; ++k)
      cout << "----" << "----+";
  cout << endl;
  for (int n = 1; n <= N; ++n)
  {
      cout << "n: " << setw(3) << n << " | ";
      for (int k = 1; k <= n; ++k)
      {
          pair<int,int> ans = solve_naive(n, k);
          pair<int,int> ans2 = solve(n, k);
          if (ans2 != ans)
          {
              cerr << "FAIL" << n << " " << k << endl;
          }
          cout << setw(4) << ans.first << setw(4) << ans.second << "|";
      }
      cout << endl;
  }
  return;
  */
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    int n, k;
    cin >> n >> k;
    pair<int, int> ans = solve(n, k);
    cout << "Case #" << t + 1 << ": " << ans.first << " " << ans.second << '\n';
  }
}
