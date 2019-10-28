#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
  int T;
  std::cin >> T;
  for (auto t = 1; t <= T; ++t) {
    int N, P;
    std::cin >> N >> P;
    std::vector<int> rec(N);
    for (auto i = 0; i < N; ++i)
      std::cin >> rec[i];
    std::vector<std::vector<int>> pac(N);
    for (auto i = 0; i < N; ++i) {
      std::vector<int> mypac(P);
      for (auto j = 0; j < P; ++j)
        std::cin >> mypac[j];
      pac[i] = mypac;
    }
    auto r = 0;
    if (N == 1) {
      auto cnt = 0;
      for (auto i = 0; i < P; ++i) {
        int nb = (pac[0][i] / static_cast<double>(rec[0])) + .5;
        if (!nb)
          continue;
        auto need = nb * rec[0];
        if ((pac[0][i] * 10 <= 11 * need) and (10 * pac[0][i] >= 9 * need))
          ++cnt;
      }
      r = cnt;
    } else {
      std::sort(pac[1].begin(), pac[1].end());
      do {
        auto cnt = 0;
        for (auto i = 0; i < P; ++i) {
          // double cnb0 = (pac[0][i] / static_cast<double>(rec[0]));
          // double cnb1 = (pac[1][i] / static_cast<double>(rec[1]));

          int nb0 = (pac[0][i] / rec[0]);
          int nb1 = (pac[1][i] / rec[1]);
          int mymin = nb0;
          int mymax = nb0;
          if (nb1 < nb0)
            mymin = nb1;
          if (mymin < 1)
            mymin = 1;
          if (nb1 > nb0)
            mymax = nb1;
          // auto nb = nb0;
          // if(nb1 < nb)
          //   nb = nb1;
          for (auto nb = mymin; nb <= mymax + 1; ++nb) {
            auto need0 = nb * rec[0];
            auto need1 = nb * rec[1];
            if ((pac[0][i] * 10 <= 11 * need0) and
                (10 * pac[0][i] >= 9 * need0) and
                (pac[1][i] * 10 <= 11 * need1) and
                (10 * pac[1][i] >= 9 * need1)) {
              ++cnt;
              break;
            }
          }
        }
        if (cnt > r)
          r = cnt;
      } while (std::next_permutation(pac[1].begin(), pac[1].end()));
    }

    std::cout << "Case #" << t << ": " << r << '\n';
  }
}
