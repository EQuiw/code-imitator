#include <algorithm>
#include <functional>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <vector>
#define _FILE_INPUT 0

typedef std::pair<long long int, long long int> lp;
int a[1003];

void process(int TEST_CASE) {
  long long int dest;
  int n;
  std::vector<lp> horse;

  scanf("%lld%d", &dest, &n);
  for (int i = 0; i < n; i++) {
    long long int pos, vel;
    scanf("%lld%lld", &pos, &vel);
    horse.push_back(std::make_pair(pos, vel));
  }
  std::sort(horse.begin(), horse.end(), std::greater<lp>());

  double ans = 0.0;
  for (int i = 0; i < horse.size(); i++) {
    double est = (double)(dest - horse[i].first) / (horse[i].second);
    ans = std::max(ans, est);
  }

  printf("Case #%d: %.6lf\n", TEST_CASE, dest / ans);
}

int main() {
#if _FILE_INPUT
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    process(i);
  }

#if _FILE_INPUT
  fclose(stdin);
  fclose(stdout);
#endif
}