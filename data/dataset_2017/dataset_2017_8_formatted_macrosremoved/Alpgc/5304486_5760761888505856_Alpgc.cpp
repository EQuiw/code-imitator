#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
string brd[27];
int rep[27];
int r, c, t;
int main() {
  cin >> t;
  for (int T = 0, __ = t; T < __; T++) {
    cin >> r >> c;
    int fir = -1, ls = -1;
    memset(rep, -1, sizeof rep);
    for (int i = 0, __ = r; i < __; i++) {
      cin >> brd[i];
      int grow = 0;
      char k = '?';
      for (int j = 0, __ = c; j < __; j++)
        if (brd[i][j] != '?') {
          grow = 1;
          k = brd[i][j];
          break;
        }
      for (int j = 0, __ = c; j < __; j++) {
        if (brd[i][j] != '?')
          k = brd[i][j];
        else
          brd[i][j] = k;
      }
      if (grow && fir == -1)
        fir = i;
      if (!grow)
        rep[i] = ls;
      else
        ls = i;
    }
    cout << "Case #" << T + 1 << ":" << endl;
    for (int i = 0, __ = r; i < __; i++) {
      if (i < fir)
        cout << brd[fir] << endl;
      else if (~rep[i])
        cout << brd[rep[i]] << endl;
      else
        cout << brd[i] << endl;
    }
  }
}
