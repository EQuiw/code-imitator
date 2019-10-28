#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

void print(int testNo, double ans) {
  cout << "Case #" << testNo << ": " << ans << endl;
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;

  cout << fixed;
  cout.precision(6);

  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int D, N;
    cin >> D >> N;
    vector<int> K(N);
    vector<int> S(N);

    int k, s;
    for (int i = 0; i < N; ++i) {
      cin >> k >> s;
      K[i] = k;
      S[i] = s;
    }

    double ans = numeric_limits<double>::max();

    for (int i = 0; i < N; ++i) {
      double x = static_cast<double>(D) * S[i] / (D - K[i]);
      ans = min(ans, x);
    }

    print(testNo, ans);
  }
}
