#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef long long int ll;

int main() {
  int T;
  cin >> T;

  cout << fixed << setprecision(7);

  for (int i = 0; i < T; i++) {
    int N, Q;
    cin >> N >> Q;

    vector<ll> d(N), s(N);
    for (int j = 0; j < N; j++) {
      cin >> d[j] >> s[j];
    }

    vector<ll> dist(N);
    int temp;
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        cin >> temp;
        if (j + 1 == k) {
          dist[j] = temp;
        }
      }
    }

    for (int j = 0; j < Q; j++) {
      cin >> temp >> temp;
    }

    vector<double> time(N);
    for (int j = 0; j < N - 1; j++) {
      double bestTime = -1;
      // cout << "dist " << dist[j] << endl;
      if (j == 0) {
        bestTime = 0;
      } else {
        for (int k = 0; k < j; k++) {
          // cout << k << " " << d[k] << endl;
          if (d[k] >= 0 && (bestTime == -1 || bestTime > time[k])) {
            bestTime = time[k];
          }
        }
      }

      time[j] = bestTime;
      // cout << time[j] << endl;

      for (int k = 0; k < j + 1; k++) {
        d[k] -= dist[j];
        time[k] += (double)dist[j] / (double)s[k];
      }
    }

    double res = 1e20;
    for (int j = 0; j < N - 1; j++) {
      if (d[j] >= 0) {
        res = min(res, time[j]);
      }
    }

    cout << "Case #" << i + 1 << ": " << res << endl;
  }

  return 0;
}
