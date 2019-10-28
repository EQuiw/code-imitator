#include <bits/stdc++.h>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    long long n, k;
    cin >> n >> k;
    map<long long, long long> cnt;
    cnt[n] += 1;
    long long ans = n;
    while (k > 0) {
      long long gap = cnt.rbegin()->first;
      long long num = cnt[gap];
      ans = gap;
      k -= num;
      cnt.erase(--cnt.end());
      if (gap % 2 == 0) {
        cnt[gap / 2] += num;
        cnt[gap / 2 - 1] += num;
      } else {
        cnt[gap / 2] += num + num;
      }
    }
    // ans = cnt.rbegin()->first;
    long long L = ans / 2;
    long long R = ans - L - 1;
    cout << "Case #" << tc << ": " << max(L, R) << ' ' << min(L, R) << endl;
  }
  return 0;
}
