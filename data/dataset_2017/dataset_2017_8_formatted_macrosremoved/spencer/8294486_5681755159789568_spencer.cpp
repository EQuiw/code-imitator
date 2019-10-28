#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve_case() {
  int N, Q;
  cin >> N >> Q;

  struct Horse {
    int max_distance, speed;
  };
  auto horses = vector<Horse>(N);
  for (auto &h : horses)
    cin >> h.max_distance >> h.speed;

  auto locations = vector<ll>(N);
  for (auto i = 0; i < N; i++) {
    auto row = vector<int>(N);
    for (auto &x : row)
      cin >> x;
    if (i != N - 1)
      locations[i + 1] = locations[i] + row[i + 1];
  }

  int U, V;
  cin >> U >> V;

  auto dp = vector<double>(N, numeric_limits<double>::infinity());
  dp[0] = 0;
  for (auto i = 0; i < N; i++) {
    for (auto j = i + 1; j < N; j++) {
      const auto dx = locations[j] - locations[i];
      if (dx > horses[i].max_distance)
        break;
      dp[j] = min(dp[j], dp[i] + double(dx) / horses[i].speed);
    }
  }
  cout << dp[N - 1] << endl;
}

int main() {
  cout << fixed << setprecision(9);

  int T;
  cin >> T;
  for (auto t = 1; t <= T; t++) {
    cout << "Case #" << t << ": ";
    solve_case();
  }
}
