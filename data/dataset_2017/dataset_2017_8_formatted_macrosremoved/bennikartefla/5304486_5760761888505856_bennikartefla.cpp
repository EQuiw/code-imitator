#include <bits/stdc++.h>
using namespace std;

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
  for (int u = (0); u < (t); u++) {
    int n, m;
    cin >> n >> m;
    char at[500][500];
    bool vis[500][500];
    memset(vis, 0, sizeof(vis));
    for (int i = (0); i < (n); i++)
      for (int a = (0); a < (m); a++)
        cin >> at[i][a];
    for (int i = (0); i < (n); i++)
      for (int a = (0); a < (m); a++) {
        if (at[i][a] != '?' && !vis[i][a]) {
          vis[i][a] = true;
          int startx = a;
          int endx = a;
          char am = at[i][a];
          for (int a2 = (a + 1); a2 < (m); a2++) {
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
          for (int i2 = (i + 1); i2 < (n); i2++) {
            bool can = true;
            for (int a2 = (startx); a2 < (endx + 1); a2++)
              if (at[i2][a2] != '?')
                can = false;
            if (can) {
              for (int a2 = (startx); a2 < (endx + 1); a2++) {
                at[i2][a2] = am;
                vis[i2][a2] = true;
              }
            } else
              break;
          }
          for (int i2 = i - 1; i2 >= 0; i2--) {
            bool can = true;
            for (int a2 = (startx); a2 < (endx + 1); a2++)
              if (at[i2][a2] != '?')
                can = false;
            if (can) {
              for (int a2 = (startx); a2 < (endx + 1); a2++) {
                at[i2][a2] = am;
                vis[i2][a2] = true;
              }
            } else
              break;
          }
        }
      }
    fout << "Case #" << u + 1 << ":" << endl;
    for (int i = (0); i < (n); i++) {
      for (int a = (0); a < (m); a++)
        fout << at[i][a];
      fout << endl;
    }
  }
  return 0;
}
