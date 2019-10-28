#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void mf() {
  // freopen("input.in","r",stdin);

  freopen("Bsmall.in", "r", stdin);
  freopen("Bsmall.ou", "w", stdout);

  // freopen("Blarge.in","r",stdin);
  // freopen("Blarge.ou","w",stdout);
}
ll n, s;
ll a[30], b[30];
void solve() {
  memset(a, 0, sizeof a);
  memset(b, 0, sizeof b);
  ll s;
  cin >> s;
  int n = 0;
  while (s > 0) {
    n++;
    a[n] = s % 10;
    s /= 10;
  }
  b[n] = a[n];
  for (int i = n; i >= 1; i--) {
    b[i] = a[i];
    if (b[i] < b[i + 1]) {
      int j = i;
      while (b[j] < b[j + 1] && (j + 1) <= n) {
        j++;
        b[j]--;
      }
      for (int k = j - 1; k >= 1; k--)
        b[k] = 9;
      break;
    }
  }
  while (b[n] == 0)
    n--;
  for (int i = n; i >= 1; i--)
    cout << b[i];
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
#ifdef tuanh
  mf();
#endif
  int ntest;
  cin >> ntest;
  for (int nt = 1; nt <= ntest; nt++) {
    cout << "Case #" << nt << ": ";
    solve();
  }

  return 0;
}