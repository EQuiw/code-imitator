#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// How many tidy numbers are in [1..N]?
ll count_tidy(ll N) {
  const auto log = 20;
  auto digits = vector<int>();
  while (N != 0) {
    digits.push_back(int(N % 10));
    N /= 10;
  }
  digits.resize(log);

  static auto dp = new ll[log][2][10];
  memset(dp, -1, sizeof(ll) * log * 2 * 10);
  const function<ll(int, bool, int)> f = [&](const int i, const bool tight,
                                             const int last) {
    if (i == -1)
      return 1LL;

    auto &result = dp[i][tight][last];
    if (result != -1)
      return result;

    result = 0;
    for (auto d = last; d <= 9; d++) {
      if (tight && d > digits[i])
        continue;
      result += f(i - 1, tight && d == digits[i], d);
    }
    return result;
  };
  return f(log - 1, true, 0);
}

ll solve_case() {
  ll N;
  cin >> N;

  const auto goal = count_tidy(N);

  auto lower = 1LL, upper = N;
  while (lower < upper) {
    const auto guess = (lower + upper) / 2;
    if (count_tidy(guess) == goal)
      upper = guess;
    else
      lower = guess + 1;
  }
  return lower;
}

int main() {
  int T;
  cin >> T;

  for (auto t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve_case() << endl;
}
