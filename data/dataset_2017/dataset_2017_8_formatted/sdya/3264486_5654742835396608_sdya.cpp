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

map<long long, long long> M;

pair<long long, long long> trivial(long long n, long long k) {
  vector<bool> a(n + 2, false);
  a[0] = a[n + 1] = true;

  pair<long long, long long> res;
  for (int i = 0; i < k; ++i) {
    pair<long long, long long> best = make_pair(-1, -1);
    int index = -1;

    for (int j = 1; j <= n; ++j) {
      if (a[j] == true) {
        continue;
      }

      long long l = 0, r = 0;
      for (int k = j - 1; k >= 0; --k) {
        if (!a[k]) {
          ++l;
        } else {
          break;
        }
      }

      for (int k = j + 1; k <= n + 1; ++k) {
        if (!a[k]) {
          ++r;
        } else {
          break;
        }
      }

      if (min(l, r) > best.first) {
        best = make_pair(min(l, r), max(l, r));
        index = j;
      } else if (min(l, r) == best.first && max(l, r) > best.second) {
        best = make_pair(min(l, r), max(l, r));
        index = j;
      }
    }

    // cout << best.first << " " << best.second << " " << index << endl;

    a[index] = true;
    res = best;
  }

  return res;
}

void solve(int test) {
  M.clear();
  long long n, k;

  cin >> n >> k;
  long long oldk = k;
  M[n] = 1;

  long long len = 0;
  while (k > 0) {
    pair<long long, long long> p = *M.rbegin();

    long long d = min(k, p.second);

    len = p.first;

    M[p.first] -= d;
    k -= d;

    M[(p.first - 1) / 2] += d;
    M[p.first / 2] += d;

    if (M[p.first] == 0) {
      M.erase(p.first);
    }
  }

  /*if (make_pair((len - 1) / 2, len / 2) != trivial(n, oldk)) {
      cout << "BAD " << trivial(n, oldk).first << " " << trivial(n, oldk).second
  << endl;
  }*/
  printf("Case #%d: %lld %lld\n", test, len / 2, (len - 1) / 2);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
    cerr << i + 1 << ": " << clock() << endl;
  }

  return 0;
}