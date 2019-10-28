#include <algorithm>
#include <array>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;

double compute(int N, const vector<double> &E, const vector<double> &S,
               const vector<vector<double>> &D, int U, int V, double curE = 0.0,
               double curS = 0.0) {
  double res = 0.0;
  for (int i = U; i < V; i++) {
    double dist = D[i][i + 1];
    if (curE < dist || (curS == S[i] && curE < E[i])) {
      // Force change
      curE = E[i];
      curS = S[i];

      curE -= dist;
      res += dist / curS;
    } else {
      // Try change
      double t1 =
          dist / S[i] + compute(N, E, S, D, i + 1, V, E[i] - dist, S[i]);
      double t2 =
          dist / curS + compute(N, E, S, D, i + 1, V, curE - dist, curS);
      return res + min(t1, t2);
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cout << setprecision(12);

  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N, Q;
    cin >> N >> Q;

    vector<double> E(N);
    vector<double> S(N);
    for (int i = 0; i < N; i++) {
      cin >> E[i] >> S[i];
    }

    vector<vector<double>> D(N, vector<double>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> D[i][j];
      }
    }

    cout << "Case #" << t + 1 << ":";
    for (int q = 0; q < Q; q++) {
      int U, V;
      cin >> U >> V;
      U--;
      V--;

      double res = compute(N, E, S, D, U, V);

      cout << " " << res;
    }
    cout << endl;
  }

  return 0;
}
