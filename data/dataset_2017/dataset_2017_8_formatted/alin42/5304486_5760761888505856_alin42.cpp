#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char G[27][27];
int l[27], r[27], u[27], d[27];
char ans[27][27];
int row, col;
bool valid(int a, int b, int c, int e, int cc) {
  if (a <= 0)
    return false;
  if (b > col)
    return false;
  if (c <= 0)
    return false;
  if (e > row)
    return false;
  for (int i = c; i <= e; i++)
    for (int j = a; j <= b; j++) {
      if ((ans[i][j] != ('A' + cc)) && (ans[i][j] != '?'))
        return false;
    }
  return true;
}
int main() {
  ios::sync_with_stdio(0);
  freopen("readable.txt", "w", stdout);
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    cout << "Case #" << ca << ": " << endl;
    cin >> row >> col;
    for (int i = 1; i <= row; i++)
      for (int j = 1; j <= col; j++) {
        cin >> G[i][j];
        ans[i][j] = G[i][j];
      }
    memset(r, 0, sizeof r);
    memset(d, 0, sizeof d);
    for (int i = 0; i < 27; i++)
      l[i] = 100, u[i] = 100;
    for (int i = 1; i <= row; i++)
      for (int j = 1; j <= col; j++)
        if (G[i][j] != '?') {
          int x = G[i][j] - 'A';
          l[x] = min(l[x], j);
          r[x] = max(r[x], j);
          u[x] = min(u[x], i);
          d[x] = max(d[x], i);
        }
    for (int i = 0; i < 26; i++)
      if (l[i] != 100) {
        while (valid(l[i] - 1, r[i], u[i], d[i], i))
          l[i]--;
        while (valid(l[i], r[i] + 1, u[i], d[i], i))
          r[i]++;
        while (valid(l[i], r[i], u[i] - 1, d[i], i))
          u[i]--;
        while (valid(l[i], r[i], u[i], d[i] + 1, i))
          d[i]++;
        // cout<<l[i]<<" "<<r[i]<<" "<<u[i]<<" "<<d[i]<<endl;
        for (int a = u[i]; a <= d[i]; a++)
          for (int b = l[i]; b <= r[i]; b++) {
            ans[a][b] = 'A' + i;
          }
      }
    for (int i = 1; i <= row; i++) {
      for (int j = 1; j <= col; j++)
        cout << ans[i][j];
      cout << endl;
    }
  }
  return 0;
}

// g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt"
// "code.cpp"