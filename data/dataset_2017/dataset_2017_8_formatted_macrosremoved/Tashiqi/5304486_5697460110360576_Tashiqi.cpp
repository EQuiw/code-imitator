#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
static const long long D = 1000000007;
static const double e = pow(2, -5);
long long T, N, P;

long long solve(map<vector<long long>, long long> &res, vector<double> &R,
                vector<vector<double>> &Q, vector<long long> &X) {
  if (res.count(X) == 0) {
    for (long long i : X) {
      if (i == 0)
        return 0;
    }
    long long r = 0;
    for (long long i = 0; i < N; ++i) {
      --X[i];
      r = max(r, solve(res, R, Q, X));
      ++X[i];
    }

    long long val, m = -1, M = -1;
    for (long long i = 0; i < N; ++i) {
      if (m == -1 or m < floor(Q[i][X[i] - 1] / R[i] * 100 / 110))
        m = floor(Q[i][X[i] - 1] / R[i] * 100 / 110);
      if (M == -1 or M > ceil(Q[i][X[i] - 1] / R[i] * 100 / 90))
        M = ceil(Q[i][X[i] - 1] / R[i] * 100 / 90);
    }
    bool can = false;
    for (val = m; val <= M and !can; ++val) {
      can = true;
      for (long long i = 0; i < N; ++i) {
        if (!(R[i] * val * 90 / 100 <= Q[i][X[i] - 1] and
              Q[i][X[i] - 1] <= R[i] * val * 110 / 100)) {
          can = false;
          break;
        }
      }
    }
    if (can) {
      for (long long i = 0; i < N; ++i)
        --X[i];
      r = max(r, solve(res, R, Q, X) + 1);
      for (long long i = 0; i < N; ++i)
        ++X[i];
    }
    res[X] = r;
  }
  return res[X];
}

int main() {
  cin >> T;
  for (long long t = 0; t < T; ++t) {
    cin >> N >> P;
    vector<double> R(N);
    vector<vector<double>> Q(N, vector<double>(P));
    for (long long i = 0; i < N; ++i)
      cin >> R[i];
    for (long long i = 0; i < N; ++i) {
      for (long long j = 0; j < P; ++j)
        cin >> Q[i][j];
      sort(Q[i].begin(), Q[i].end());
    }
    map<vector<long long>, long long> res;
    vector<long long> X(N, P);
    solve(res, R, Q, X);
    cout << "Case #" << t + 1 << ": " << solve(res, R, Q, X) << endl;
  }
  return 0;
}
