#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef pair<ii, int> iii;
void open() {
  freopen("D:/OneDrive/Code/GCJ/C-small-attempt1 (1).in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out22.txt", "w", stdout);
}
int n, q, fr, to;
int energy[120];
int spd[120];
int dist[120][120];
map<iii, double> memo;

double dp(int idx, int pony, int left) {
  iii z = make_pair(ii(idx, pony), left);
  if (idx == to)
    return 0;
  if (memo.find(z) != memo.end() && memo[z] < 1e12)
    return memo[z];

  double ans = 1e12;

  if (dist[idx][idx + 1] <= left) {
    ans = min(dp(idx + 1, pony, left - dist[idx][idx + 1]) +
                  1.0 * dist[idx][idx + 1] / spd[pony],
              ans);
  }

  if (dist[idx][idx + 1] <= energy[idx]) {
    ans = min(ans, dp(idx + 1, idx, energy[idx] - dist[idx][idx + 1]) +
                       1.0 * dist[idx][idx + 1] / spd[idx]);
  }
  return memo[z] = ans;
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    scanf("%d", &n);
    scanf("%d", &q);

    for (int i = 0; i < n; i++) {
      scanf("%d", &energy[i]);
      scanf("%d", &spd[i]);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &dist[i][j]);
      }
    }

    scanf("%d", &fr);
    scanf("%d", &to);
    fr--;
    to--;
    memo.clear();

    printf("Case #%d: %.10lf\n", ct, dp(0, 0, energy[0]));

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
