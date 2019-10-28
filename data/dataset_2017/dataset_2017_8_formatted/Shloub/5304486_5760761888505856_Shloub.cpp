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
    int R, C;
    std::cin >> R >> C;
    std::vector<std::string> v(R);
    for (auto i = 0; i < R; ++i)
      std::cin >> v[i];
    std::set<char> seen{};
    for (auto i = 0; i < R; ++i)
      for (auto j = 0; j < C; ++j) {
        if (v[i][j] == '?')
          continue;
        if (seen.find(v[i][j]) != seen.end())
          continue;
        seen.insert(v[i][j]);
        auto minr = i;
        while (minr - 1 >= 0 and v[minr - 1][j] == '?')
          --minr;
        auto ok = true;
        auto minc = j;
        while (true) {
          if (minc - 1 < 0)
            break;
          for (auto ii = minr; ii <= i; ++ii)
            if (v[ii][minc - 1] != '?')
              ok = false;
          if (!ok)
            break;
          --minc;
        }
        auto maxc = j;
        ok = true;
        while (true) {
          if (maxc + 1 >= C)
            break;
          for (auto ii = minr; ii <= i; ++ii)
            if (v[ii][maxc + 1] != '?')
              ok = false;
          if (!ok)
            break;
          ++maxc;
          // std::cerr << maxc << '\n';
        }
        auto maxr = i;
        ok = true;
        while (true) {
          if (maxr + 1 >= R)
            break;
          for (auto jj = minc; jj <= maxc; ++jj)
            if (v[maxr + 1][jj] != '?')
              ok = false;
          if (!ok)
            break;
          // std::cerr << maxr << '\n';
          ++maxr;
        }
        for (auto ii = minr; ii <= maxr; ++ii)
          for (auto jj = minc; jj <= maxc; ++jj)
            v[ii][jj] = v[i][j];
      }

    std::cout << "Case #" << t << ":\n";
    for (auto &s : v)
      std::cout << s << '\n';
  }
}
