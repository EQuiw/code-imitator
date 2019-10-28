#include <bits/stdc++.h>

using namespace std;

int main() {
  int test;
  cin >> test;
  for (int cases = 1; cases <= test; cases++) {
    int N;
    int R, O, Y, G, B, V;
    cin >> N;
    cin >> R >> O >> Y >> G >> B >> V;

    int maxi = R;
    maxi = max(maxi, Y);
    maxi = max(maxi, B);

    bool ok = true;

    if (maxi > N / 2)
      ok = false;

    string res = "";
    if (ok == false) {
      res = "IMPOSSIBLE";
    } else {
      char c;
      for (int i = 0; i < N; i++)
        res += " ";
      if (R == maxi)
        c = 'R', R = 0;
      else if (Y == maxi)
        c = 'Y', Y = 0;
      else
        c = 'B', B = 0;
      for (int i = 0; i < maxi; i++) {
        res[i * 2] = c;
      }

      for (int i = 0; i < maxi; i++) {
        char c;
        int m = R;
        c = 'R';
        if (Y > m)
          m = Y, c = 'Y';
        if (B > m)
          m = B, c = 'B';

        if (c == 'R')
          R--;
        else if (c == 'Y')
          Y--;
        else if (c == 'B')
          B--;

        res[i * 2 + 1] = c;
      }

      for (int i = maxi * 2; i < N; i++) {
        if (R > 0 && res[i - 1] != 'R')
          res[i] = 'R', R--;
        else if (Y > 0 && res[i - 1] != 'Y')
          res[i] = 'Y', Y--;
        else if (B > 0 && res[i - 1] != 'B')
          res[i] = 'B', B--;
      }
    }

    cout << "Case #" << cases << ": " << res << endl;
  }
  return 0;
}
