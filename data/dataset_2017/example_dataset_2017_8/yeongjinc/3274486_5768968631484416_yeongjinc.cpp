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

const long double PI = 3.14159265359;

void print(int testNo, long double ans) {
  cout << "Case #" << testNo << ": " << ans << endl;
}

int main() {
  cout << fixed;
  cout.precision(10);

  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int N, K;
    cin >> N >> K;

    vector<pair<long double, long double> > cakes(N);
    for (int i = 0; i < N; ++i) {
      int r, h;
      cin >> r >> h;
      cakes[i].first = static_cast<long double>(r);
      cakes[i].second = static_cast<long double>(h);
    }

    auto rcmp = [](const pair<long double, long double>& a, const pair<long double, long double>& b) {
      return a.first > b.first;
    };
    auto scmp = [](const pair<long double, long double>& a, const pair<long double, long double>& b) {
      return 2.0L*PI*a.first*a.second > 2.0L*PI*b.first*b.second;
    };

    sort(cakes.begin(), cakes.end(), rcmp);
    long double ans = 0.0L;

    for (int i = 0; i <= N - K; ++i) {
      long double cur = PI*cakes[i].first*cakes[i].first + PI*2.0L*cakes[i].first*cakes[i].second;
      if (K > 1) {
        vector<pair<long double, long double> > work(cakes.begin() + i + 1, cakes.end());
        sort(work.begin(), work.end(), scmp);
        for (int i = 0; i < K - 1; ++i)
          cur += PI*2.0L*work[i].first*work[i].second;
      }
      ans = max(cur, ans);
    }

    print(testNo, ans);
  }
}
