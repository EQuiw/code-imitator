#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define iter(it, c)                                                            \
  for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1 << 31);
const double pi = acos(-1);

int main() {
  cin.sync_with_stdio(false);
  ofstream fout("ans.txt");
  int t;
  cin >> t;
  rep(u, 0, t) {
    int n, m;
    cin >> n >> m;
    char at[500][500];
    bool vis[500][500];
    memset(vis, 0, sizeof(vis));
    rep(i, 0, n) rep(a, 0, m) cin >> at[i][a];
    rep(i, 0, n) rep(a, 0, m) {
      if (at[i][a] != '?' && !vis[i][a]) {
        vis[i][a] = true;
        int startx = a;
        int endx = a;
        char am = at[i][a];
        rep(a2, a + 1, m) {
          if (at[i][a2] == '?') {
            at[i][a2] = am;
            vis[i][a2] = true;
            endx++;
          } else
            break;
        }
        for (int a2 = a - 1; a2 >= 0; a2--) {
          if (at[i][a2] == '?') {
            at[i][a2] = am;
            vis[i][a2] = true;
            startx--;
          } else
            break;
        }
        // found startx and endx
        rep(i2, i + 1, n) {
          bool can = true;
          rep(a2, startx, endx + 1) if (at[i2][a2] != '?') can = false;
          if (can) {
            rep(a2, startx, endx + 1) {
              at[i2][a2] = am;
              vis[i2][a2] = true;
            }
          } else
            break;
        }
        for (int i2 = i - 1; i2 >= 0; i2--) {
          bool can = true;
          rep(a2, startx, endx + 1) if (at[i2][a2] != '?') can = false;
          if (can) {
            rep(a2, startx, endx + 1) {
              at[i2][a2] = am;
              vis[i2][a2] = true;
            }
          } else
            break;
        }
      }
    }
    fout << "Case #" << u + 1 << ":" << endl;
    rep(i, 0, n) {
      rep(a, 0, m) fout << at[i][a];
      fout << endl;
    }
  }
  return 0;
}
