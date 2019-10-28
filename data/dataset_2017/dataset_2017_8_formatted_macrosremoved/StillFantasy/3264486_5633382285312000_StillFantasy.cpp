#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<long long> v;
  queue<long long> q;

  q.push(0);

  while (!q.empty()) {
    long long val = q.front();
    q.pop();

    v.push_back(val);

    int now = val % 10;
    if (now == 0)
      now = 1;
    for (int i = now; i <= 9; i++) {
      if (val * 10 + i > 1000000000000000000LL)
        continue;
      q.push(val * 10 + i);
    }
  }

  int kase = 0, test;
  scanf("%d", &test);
  while (test--) {
    long long n;
    scanf("%lld", &n);
    int idx = lower_bound(v.begin(), v.end(), n) - v.begin();
    if (v[idx] != n)
      idx--;
    printf("Case #%d: %lld\n", ++kase, v[idx]);
  }
  return 0;
}
