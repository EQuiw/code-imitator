#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

void print(int testNo, int maxNum) {
  cout << "Case #" << testNo << ": " << maxNum << endl;
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int N, P;
    cin >> N >> P;
    vector<int> R(N);
    vector<vector<int> > Q(N, vector<int>(P));

    for (int i = 0; i < N; ++i)
      cin >> R[i];

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < P; ++j)
        cin >> Q[i][j];
      sort(Q[i].begin(), Q[i].end());
    }

    vector<int> lastSelected(N);
    int ans = 0;

    for (int i = 0; i < P; ++i) {
      int minKit = ceil(static_cast<double>(Q[0][i]) / (1.1 * R[0]));
      int maxKit = floor(static_cast<double>(Q[0][i]) / (0.9 * R[0]));
      // cout << Q[0][i] << ' ' << minKit <<  ' ' << maxKit << endl;

      vector<int> cur(N);
      cur[0] = i;
      for (int j = minKit; j <= maxKit; ++j) {

        int k;
        for (k = 1; k < N; ++k) {
          int minIng = ceil(static_cast<double>(R[k]) * j * 0.9);
          int maxIng = floor(static_cast<double>(R[k]) * j * 1.1);
          if (minIng > maxIng) break;

          auto it = lower_bound(Q[k].begin() + lastSelected[k], Q[k].end(), minIng);
          if (it == Q[k].end()) break;
          if (*it > maxIng) break;

          lastSelected[k] = it - Q[k].begin();
        }
        if (k == N) {
          lastSelected = cur;
          ++ans;
          break;
        }
      }
    }
    print(testNo, ans);
  }
}
