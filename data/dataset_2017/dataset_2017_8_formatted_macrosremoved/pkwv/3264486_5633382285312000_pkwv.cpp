#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef long long ll;
typedef double db;
const int N = 25;

ll d[N];

int to_digit(ll n) {
  int l(0);
  while (n) {
    d[l++] = n % 10;
    n /= 10;
  }
  return l;
}

ll to_int(int l) {
  ll res(0);
  while (--l >= 0) {
    res = res * 10 + d[l];
  }
  return res;
}

int main() {

  int T;
  scanf("%d", &T);
  for (int ca = 1; ca <= T; ca++) {
    ll n;
    scanf("%lld", &n);
    int l = to_digit(n);
    d[l] = 0;
    for (int i = l - 1; i >= 0; i--) {
      if (d[i] < d[i + 1]) {
        int j(i + 1);
        while (j < l && d[j] > d[j - 1])
          d[j++]--;
        i = j - 2;
        while (i >= 0)
          d[i--] = 9;
        break;
      }
    }
    printf("Case #%d: %lld\n", ca, to_int(l));
  }
  return 0;
}
