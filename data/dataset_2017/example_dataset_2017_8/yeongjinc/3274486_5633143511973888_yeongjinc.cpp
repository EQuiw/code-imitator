#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <climits>
#include <utility>
#include <queue>
#include <stack>

using namespace std;

void print(int testNo, long double ans) {
  cout << "Case #" << testNo << ": " << ans << endl;
}

int main() {
  cout << fixed;
  cout.precision(8);
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int N, K;
    long double U;
    cin >> N >> K >> U;
    vector<long double> P(N);
    long double sum = 0.0L;
    for (int i = 0; i < N; ++i) {
      long double p;
      cin >> p;
      P[i] = p;
      sum += p;
    }
    sort(P.begin(), P.end());
    while (U > 0.000001L) {
      int equal = 1;
      for (int i = 1; i < N; ++i) {
        if (P[i-1] == P[i])
          ++equal;
        else
          break;
      }

      if (equal == N) {
        for (int i = 0; i < N; ++i)
          P[i] += U / equal;
        U = 0.0L;
      } else {
        long double inc = P[equal] - P[equal-1];
        inc = min(inc, U / equal);
        for (int i = 0; i < equal; ++i) {
          P[i] += inc;
          U -= inc;
        }
      }
    }

    long double ans = 1.0L;
    for (int i = 0; i < N; ++i)
      ans *= P[i];

    print(testNo, ans);
  }
}
