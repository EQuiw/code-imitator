#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; Case++) {
    ll N, K;
    scanf("%lld%lld", &N, &K);
    map<ll, ll> s;
    s[N]++;
    ll ansy = 0, ansz = 0;
    for (map<ll, ll>::reverse_iterator cur = s.rbegin(); cur != s.rend();
         cur++) {
      ll z = (cur->first - 1) / 2, y = (cur->first - 1) - z;
      if (K <= cur->second) {
        ansz = z;
        ansy = y;
        break;
      } else {
        K -= cur->second;
        s[z] += cur->second;
        s[y] += cur->second;
      }
    }
    printf("Case #%d: %lld %lld\n", Case, ansy, ansz);
  }
}
