#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int maxn = 1007;

void mf() {
  // freopen("input.in","r",stdin);

  freopen("Asmall.in", "r", stdin);
  freopen("Asmall.ou", "w", stdout);

  // freopen("Alarge.in","r",stdin);
  // freopen("Alarge.ou","w",stdout);
}
struct data {
  double k, s;
};
data a[maxn];
double d;
int n;
bool increaseCompare(const data &left, const data &right) {
  return left.k < right.k; // false->swap
}
void solve() {
  cin >> d >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i].k >> a[i].s;
  }
  sort(a, a + n, increaseCompare);
  double maxTime = -1e9;
  for (int i = n - 1; i >= 0; i--) {
    double time = (d - a[i].k) / a[i].s;
    maxTime = max(time, maxTime);
  }
  cout << setprecision(9) << fixed;
  double ans = d / maxTime;
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);

  int ntest;
  cin >> ntest;
  for (int nt = 1; nt <= ntest; nt++) {
    cout << "Case #" << nt << ": ";
    solve();
  }

  return 0;
}
