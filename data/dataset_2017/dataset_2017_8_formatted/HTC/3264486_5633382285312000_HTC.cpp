#include <cstdio>
#include <iostream>
using namespace std;

long long makeNum(int d, int len) {
  long long res = 0;
  for (int i = 0; i < len; i++) {
    res = res * 10 + d;
  }
  return res;
}
long long make10(int d, int len) {
  long long res = d;
  for (int i = 0; i < len - 1; i++) {
    res = res * 10;
  }
  return res;
}
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("BSOut.txt", "w", stdout);
  int T;
  cin >> T;
  long long N;
  for (int ca = 1; ca <= T; ca++) {
    cin >> N;
    long long ans = 0;
    int nowlen = 18;
    while (nowlen > 0) {
      for (int i = 9; i >= 1; i--) {

        long long a = 0;
        a = makeNum(i, nowlen);
        if (a <= N) {
          long long b = make10(i, nowlen);
          ans += b;
          N -= b;
          break;
        }
      }
      nowlen--;
    }

    cout << "Case #" << ca << ": " << ans << "\n";
  }

  return 0;
}
