#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
const int mod = 1e9 + 7;
#define maxn 60

int a[maxn][maxn];
long long int c[maxn];
int cnt[maxn];

multiset<long long int> st[maxn];

bool take(long long int qnt, int n) {

  for (int i = 1; i <= n; i++) {
    long long int l = 1LL * 9 * qnt * c[i];
    l = l / 10;
    long long int u = 1LL * 11 * qnt * c[i];
    u = u / 10;

    if (st[i].empty())
      return 0;
    if (*(--st[i].end()) < l)
      return 0;
    if ((*st[i].begin()) > u)
      return 0;
  }
  for (int i = 1; i <= n; i++) {
    long long int u = 1LL * 9 * qnt * c[i];
    u = u / 10;
    multiset<long long int>::iterator it = st[i].lower_bound(u);
    st[i].erase(it);
  }
  return 1;
}

void solve(int ind) {
  int n, p;
  cin >> n >> p;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= n; i++)
    st[i].clear();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= p; j++) {
      cin >> a[i][j];
      st[i].insert(a[i][j]);
    }
  }
  int ans = 0;
  for (int i = 1; i <= 1000500; i++) {
    while (1) {
      if (take(i, n))
        ans++;
      else
        break;
    }
  }
  cout << "Case #" << ind << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
  return 0;
}