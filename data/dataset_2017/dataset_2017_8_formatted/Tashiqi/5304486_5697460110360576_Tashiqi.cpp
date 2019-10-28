#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#define ll long long
#define sort(A) sort(A.begin(), A.end())
#define rsort(A) sort(A.rbegin(), A.rend())
using namespace std;
static const ll D = 1000000007;
static const double e = pow(2, -5);
ll T, N, P;

ll solve(map<vector<ll>, ll> &res, vector<double> &R, vector<vector<double>> &Q,
         vector<ll> &X) {
  if (res.count(X) == 0) {
    for (ll i : X) {
      if (i == 0)
        return 0;
    }
    ll r = 0;
    for (ll i = 0; i < N; ++i) {
      --X[i];
      r = max(r, solve(res, R, Q, X));
      ++X[i];
    }

    ll val, m = -1, M = -1;
    for (ll i = 0; i < N; ++i) {
      if (m == -1 or m < floor(Q[i][X[i] - 1] / R[i] * 100 / 110))
        m = floor(Q[i][X[i] - 1] / R[i] * 100 / 110);
      if (M == -1 or M > ceil(Q[i][X[i] - 1] / R[i] * 100 / 90))
        M = ceil(Q[i][X[i] - 1] / R[i] * 100 / 90);
    }
    bool can = false;
    for (val = m; val <= M and !can; ++val) {
      can = true;
      for (ll i = 0; i < N; ++i) {
        if (!(R[i] * val * 90 / 100 <= Q[i][X[i] - 1] and
              Q[i][X[i] - 1] <= R[i] * val * 110 / 100)) {
          can = false;
          break;
        }
      }
    }
    if (can) {
      for (ll i = 0; i < N; ++i)
        --X[i];
      r = max(r, solve(res, R, Q, X) + 1);
      for (ll i = 0; i < N; ++i)
        ++X[i];
    }
    res[X] = r;
  }
  return res[X];
}

int main() {
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    cin >> N >> P;
    vector<double> R(N);
    vector<vector<double>> Q(N, vector<double>(P));
    for (ll i = 0; i < N; ++i)
      cin >> R[i];
    for (ll i = 0; i < N; ++i) {
      for (ll j = 0; j < P; ++j)
        cin >> Q[i][j];
      sort(Q[i]);
    }
    map<vector<ll>, ll> res;
    vector<ll> X(N, P);
    solve(res, R, Q, X);
    cout << "Case #" << t + 1 << ": " << solve(res, R, Q, X) << endl;
  }
  return 0;
}
