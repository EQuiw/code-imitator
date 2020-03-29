#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/A-small-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int n, k;

double memo[1010][1010];

pair<double, double> pancake[1010];

double tinggiarea(int idx) {
  // cout << idx << " " << 2.0 * PI * pancake[idx].first * pancake[idx].second
  // << endl;
  return 2.0 * acos(-1.0) * pancake[idx].first * pancake[idx].second;
}

double base(int idx) {
  // cout << PI * pancake[idx].first * pancake[idx].second << endl;
  return acos(-1.0) * pancake[idx].first * pancake[idx].first;
}

double dp(int idx, int sisa) {
  if (sisa == 0)
    return 0;
  if (idx < 0)
    return -1000000000;
  if (memo[idx][sisa] >= 0)
    return memo[idx][sisa];

  double ans = 0;
  if (sisa == k) {
    ans = max(dp(idx - 1, sisa),
              dp(idx - 1, sisa - 1) + tinggiarea(idx) + base(idx));
  } else if (sisa > 0) {
    ans = max(dp(idx - 1, sisa), dp(idx - 1, sisa - 1) + tinggiarea(idx));
  }

  return memo[idx][sisa] = ans;
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    scanf("%d", &n);
    scanf("%d", &k);
    for (int i = 0; i < n; i++) {
      cin >> pancake[i].first >> pancake[i].second;
    }

    for (int i = 0; i <= 1001; i++)
      for (int j = 0; j <= 1001; j++)
        memo[i][j] = -1.0;

    sort(pancake, pancake + n);
    printf("Case #%d: %.10lf\n", ct, dp(n - 1, k));

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
