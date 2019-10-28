#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  int T;
  std::cin >> T;
  for (auto t = 1; t <= T; ++t) {
    long long int D, N;
    std::cin >> D >> N;
    std::vector<std::pair<long long int, long long int>> ks(N);
    for (auto i = 0; i < N; ++i)
      std::cin >> ks[i].first >> ks[i].second;
    std::sort(ks.begin(), ks.end(),
              std::greater<std::pair<long long int, long long int>>());
    auto r = 0.;
    auto max = 0.;
    for (auto &h : ks) {
      auto d = D - h.first;
      auto t = d / (h.second * 1.);
      if (t > max)
        max = t;
    }
    r = D / max;
    std::cout << "Case #" << t << ": " << std::setprecision(10) << r << '\n';
  }
}
