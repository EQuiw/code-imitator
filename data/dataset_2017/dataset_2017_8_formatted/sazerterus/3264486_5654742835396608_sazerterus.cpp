#include <bits/stdc++.h>

using namespace std;

pair<long long, long long> func(long long n, long long k) {
  if (k == 1) {
    if (n % 2 == 0) {
      return make_pair(n / 2, n / 2 - 1);
    }
    return make_pair(n / 2, n / 2);
  }
  --k;
  if (n % 2 == 0) {
    long long lef = (n - 1) / 2;
    long long righ = n / 2;
    if (k % 2) {
      return func(righ, (k + 1) / 2);
    }
    return func(lef, k / 2);
  }
  return func(n / 2, (k + 1) / 2);
}

int main() {
  freopen("A.txt", "r", stdin);
  freopen("W.txt", "w", stdout);
  int t;
  cin >> t;
  int index = 1;
  while (t--) {
    long long n, k;
    cin >> n >> k;
    cout << "Case #" << index++ << ": " << func(n, k).first << " "
         << func(n, k).second << endl;
  }
  return 0;
}
