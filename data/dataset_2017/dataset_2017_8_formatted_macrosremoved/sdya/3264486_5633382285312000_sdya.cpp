#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

const long long inf = 1000000000000000000LL;

vector<long long> res;

void rec(long long value, long long d) {
  if (value >= inf) {
    return;
  }
  res.push_back(value);
  for (long long i = d; i <= 9; ++i) {
    if (value < inf / 10LL) {
      rec(value * 10LL + i, i);
    }
  }
}

void solve(int test) {
  long long n;
  cin >> n;

  int index = upper_bound(res.begin(), res.end(), n) - res.begin() - 1;
  printf("Case #%d: %lld\n", test, res[index]);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  for (int i = 1; i <= 9; ++i) {
    rec(i, i);
  }

  sort(res.begin(), res.end());
  cerr << "Res size: " << res.size() << endl;

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
    cerr << i + 1 << ": " << clock() << endl;
  }

  return 0;
}
