
#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

FILE *ifile = nullptr;
std::ofstream ofile;

void solve(int _case) {
  std::uint64_t n = 0;
  std::uint64_t p = 0;
  std::uint64_t v = 0;
  std::vector<std::uint64_t> etalon;
  std::vector<std::uint64_t> index;
  std::vector<std::vector<std::pair<std::uint64_t, std::uint64_t>>> packages;
  std::uint64_t counter = 0;

  std::fscanf(ifile, "%ld %ld", &n, &p);

  etalon.resize(n);
  packages.resize(n);
  index.resize(n);

  for (auto i = 0; i < n; ++i) {
    index[i] = 0;
    std::fscanf(ifile, "%ld", &etalon[i]);
  }

  for (auto i = 0; i < n; ++i) {
    packages[i].reserve(p);
    auto e = etalon[i];
    std::uint64_t minE = e - std::uint64_t(e * 0.1);
    std::uint64_t maxE = e * 1.1;
    for (auto j = 0; j < p; ++j) {
      std::fscanf(ifile, "%ld", &v);
      auto minP = v / maxE;
      auto maxP = v / minE;
      if (minP * maxE != v)
        ++minP;
      if (minP > maxP)
        continue;
      packages[i].push_back(std::make_pair(minP, maxP));
    }
    std::sort(packages[i].begin(), packages[i].end(),
              [](const std::pair<std::uint64_t, std::uint64_t> &a,
                 const std::pair<std::uint64_t, std::uint64_t> &b) {
                if (a.first < b.first)
                  return true;
                else if (a.first > b.first)
                  return false;
                else
                  return (a.second < b.second);
              });
  }

  auto s = 1u;
  auto exit = false;
  while (s <= 1000000) {
    bool is_set = true;

    for (auto i = 0; is_set && i < n; ++i) {
      auto idx = index[i];
      while ((idx < packages[i].size()) && (packages[i][idx].second < s))
        ++idx;
      if (idx >= packages[i].size()) {
        exit = true;
        break;
      }
      index[i] = idx;
      is_set = packages[i][idx].first <= s;
    }

    if (exit)
      break;

    if (!is_set) {
      ++s;
    } else {
      for (auto i = 0; i < n; ++i)
        ++index[i];
      ++counter;
    }
  }

  ofile << "Case #" << _case << ": " << counter << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  ifile = fopen("1.in", "r");
  ofile.open("output.out");

  int n = 0;
  std::fscanf(ifile, "%d", &n);
  for (auto i = 0; i < n; ++i)
    solve(i + 1);

  ofile.close();

  return 0;
}
