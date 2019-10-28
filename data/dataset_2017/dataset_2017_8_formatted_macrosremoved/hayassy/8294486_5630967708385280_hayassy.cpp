#include <algorithm> // sort
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef long long ll;
using namespace std;

int main() {
  ll T;
  cin >> T;

  for (int t = 0; t < T; t++) {
    ll D, N;
    cin >> D >> N;

    vector<ll> Ks(N);
    vector<ll> Ss(N);
    for (int i = 0; i < N; i++) {
      cin >> Ks[i] >> Ss[i];
    }

    double max_time = 0;
    for (int i = 0; i < N; i++) {
      max_time = max(max_time, ((double)(D - Ks[i])) / (double)Ss[i]);
    }

    double ans = D / max_time;

    cout << "Case #" << t + 1 << ": " << setprecision(8) << ans << endl;
  }

  return 0;
}
