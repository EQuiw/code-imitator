
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
  int n;
  int q;

  std::pair<int, int> hourse[100];
  long double result[100];
  long double dp[100];
  int distance[100][100];

  std::fscanf(ifile, "%d %d", &n, &q);

  for (auto i = 0; i < n; ++i)
    std::fscanf(ifile, "%d %d", &hourse[i].first, &hourse[i].second);

  for (auto i = 0; i < n; ++i)
    for (auto j = 0; j < n; ++j)
      std::fscanf(ifile, "%d ", &distance[i][j]);

  for (auto q1 = 0; q1 < q; ++q1) {
    int from;
    int to;

    std::fscanf(ifile, "%d %d", &from, &to);

    for (auto i = 0; i < n; ++i)
      dp[i] = std::numeric_limits<long double>::max();

    dp[0] = 0;

    for (auto i = 0; i < (n - 1); ++i) {
      long double range = hourse[i].first;
      auto speed = hourse[i].second;
      auto start = dp[i];
      long double total = 0;
      for (auto j = i; j < (n - 1); ++j) {
        total += distance[j][j + 1];
        if (range < total)
          break;
        dp[j + 1] = std::min(dp[j + 1], start + total / speed);
      }
    }

    result[q1] = dp[n - 1];
  }

  ofile << "Case #" << _case << ":";
  for (auto i = 0; i < q; ++i)
    ofile << " " << result[i];
  ofile << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  ifile = fopen("1.in", "r");
  ofile.open("output.out");
  ofile << std::setprecision(9);

  int n = 0;
  std::fscanf(ifile, "%d", &n);
  for (auto i = 0; i < n; ++i)
    solve(i + 1);

  ofile.close();

  return 0;
}
