#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for (auto t = 1; t <= T; ++t) {
    long long n, k;
    std::cin >> n >> k;
    auto ma = 0LL;
    auto mi = 0LL;
    auto cur = n;
    // auto cur2 = n;
    auto nbcur = 1LL;
    auto nbcur2 = 0LL;
    auto i = 1LL;
    while (k >= 2 * i) {
      // auto oldcur = cur;
      i *= 2;
      --cur;
      if (cur % 2 == 1) {
        cur = cur / 2 + 1;
        // cur2 = (oldcur-1)/2;
        nbcur2 = nbcur + 2 * nbcur2;
      } else {
        cur = cur / 2;
        // cur2 = (oldcur-1)/2 - 1;
        nbcur = 2 * nbcur + nbcur2;
      }
      // std::cerr << cur << ' ' << nbcur << '\n';
      // std::cerr << cur2 << ' ' << nbcur2 << '\n';
    }
    // std::cerr << cur << '\n';
    if (k > i + nbcur - 1)
      --cur;
    --cur;
    ma = cur / 2;
    mi = cur / 2;
    if (cur % 2)
      ++ma;

    std::cout << "Case #" << t << ": " << ma << ' ' << mi << '\n';
  }
}
