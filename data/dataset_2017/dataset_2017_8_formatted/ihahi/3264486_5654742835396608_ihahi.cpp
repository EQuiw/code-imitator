#include <iostream>
#include <set>
#include <string>

using namespace std;

void solve(void);
pair<long long, long long> solveLR(pair<long long, long long> nk);

long long n;
long long k;

int main(int argc, const char *argv[]) {
  freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/Qual2017-C/in.txt", "r",
          stdin);
  freopen("/Users/iwaisatoshi/Dropbox/17Todai/CodeJam/Qual2017-C/out.txt", "w",
          stdout);
  int t;
  scanf("%d", &t);
  for (int cnt = 0; cnt < t; cnt++) {
    scanf("%lld %lld", &n, &k);
    printf("Case #%d: ", cnt + 1);
    solve();
    printf("\n");
  }
  return 0;
}

void solve(void) {
  pair<long long, long long> ans = solveLR(make_pair(n, k));
  printf("%lld %lld", ans.first, ans.second);
  return;
}

pair<long long, long long> solveLR(pair<long long, long long> nk) {
  if (nk.first == nk.second) {
    return make_pair(0, 0);
  }
  if (nk.second == 1) {
    if (nk.first % 2 == 0) {
      return make_pair(nk.first / 2, nk.first / 2 - 1);
    } else {
      return make_pair(nk.first / 2, nk.first / 2);
    }
  }

  long long newN, newK;
  newN = nk.first - 1;
  newK = nk.second - 1;
  if (newN % 2 == 0) {
    newN = newN / 2;
  } else if (newK % 2 == 0) {
    newN = newN / 2;
  } else {
    newN = newN / 2 + 1;
  }

  if (newK % 2 == 0) {
    newK = newK / 2;
  } else {
    newK = newK / 2 + 1;
  }
  return solveLR(make_pair(newN, newK));
}
