#include <bits/stdc++.h>
using namespace std;
bool compat(char c1, char c2) {
  switch (c1) {
  case 'R':
    return c2 != 'R' && c2 != 'O' && c2 != 'V';
  case 'Y':
    return c2 != 'O' && c2 != 'Y' && c2 != 'G';
  case 'B':
    return c2 != 'G' && c2 != 'B' && c2 != 'V';
  }
}
int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    string ans;
    bool possible = true;
    if (R > 0) {
      ans += "R";
      R--;
    } else if (O > 0) {
      ans += "O";
      O--;
    } else if (Y > 0) {
      ans += "Y";
      Y--;
    } else if (G > 0) {
      ans += "G";
      G--;
    } else if (B > 0) {
      ans += "B";
      B--;
    } else if (V > 0) {
      ans += "V";
      V--;
    }
    while (ans.length() < N) {
      char candidate = ' ';
      int maxi = 0;
      // cout << R << " " << Y << " " << B << endl;
      if (R > 0 && ans[ans.length() - 1] != 'R' &&
          ans[ans.length() - 1] != 'O' && ans[ans.length() - 1] != 'V') {
        if (R > maxi) {
          maxi = R;
          candidate = 'R';
        }
      }
      if (O > 0 && ans[ans.length() - 1] != 'R' &&
          ans[ans.length() - 1] != 'O' && ans[ans.length() - 1] != 'Y' &&
          ans[ans.length() - 1] != 'G' && ans[ans.length() - 1] != 'V') {
        if (O > maxi) {
          maxi = O;
          candidate = 'O';
        }
      }
      if (Y > 0 && ans[ans.length() - 1] != 'O' &&
          ans[ans.length() - 1] != 'Y' && ans[ans.length() - 1] != 'G') {
        if (Y > maxi) {
          maxi = Y;
          candidate = 'Y';
        }
      }
      if (G > 0 && ans[ans.length() - 1] != 'O' &&
          ans[ans.length() - 1] != 'Y' && ans[ans.length() - 1] != 'G' &&
          ans[ans.length() - 1] != 'B' && ans[ans.length() - 1] != 'V') {
        if (G > maxi) {
          maxi = G;
          candidate = 'G';
        }
      }
      if (B > 0 && ans[ans.length() - 1] != 'G' &&
          ans[ans.length() - 1] != 'B' && ans[ans.length() - 1] != 'V') {
        if (B > maxi) {
          maxi = B;
          candidate = 'B';
        }
      }
      if (V > 0 && ans[ans.length() - 1] != 'O' &&
          ans[ans.length() - 1] != 'G' && ans[ans.length() - 1] != 'B' &&
          ans[ans.length() - 1] != 'V' && ans[ans.length() - 1] != 'R') {
        if (V > maxi) {
          maxi = V;
          candidate = 'V';
        }
      }
      if (candidate == ' ') {
        // cout << ans << endl;
        possible = false;
        break;
      } else {
        ans += candidate;
        switch (candidate) {
        case 'R':
          R--;
          break;
        case 'O':
          O--;
          break;
        case 'Y':
          Y--;
          break;
        case 'G':
          G--;
          break;
        case 'B':
          B--;
          break;
        case 'V':
          V--;
          break;
        }
      }
    }
    if (possible && compat(ans[0], ans[ans.length() - 1])) {
      cout << "Case #" << t << ": " << ans << endl;
    } else {
      cout << "Case #" << t << ": IMPOSSIBLE" << endl;
    }
  }
  return 0;
}
