#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

string solve(int R, int Y, int B) {
  int aux[3];
  aux[0] = R;
  aux[1] = Y;
  aux[2] = B;
  for (int i = 0; i < (3); i++) {
    if (aux[i] < 0)
      return "IMPOSSIBLE";
  }
  string l;

  if (R >= Y) {
    if (Y >= B)
      l = "RYB";
    else {
      if (B > R) {
        l = "BRY";
        aux[0] = B;
        aux[1] = R;
        aux[2] = Y;
      } else {
        l = "RBY";
        aux[0] = R;
        aux[1] = B;
        aux[2] = Y;
      }
    }
  } else {
    if (R >= B) {
      l = "YRB";
      aux[0] = Y;
      aux[1] = R;
      aux[2] = B;
    } else {
      if (B >= Y) {
        l = "BYR";
        aux[0] = B;
        aux[1] = Y;
        aux[2] = R;
      } else {
        l = "YBR";
        aux[0] = Y;
        aux[1] = B;
        aux[2] = R;
      }
    }
  }

  if (aux[0] > (aux[1] + aux[2]))
    return "IMPOSSIBLE";

  string ans = "";
  for (int i = 0; i < (aux[1] - aux[2]); i++) {
    ans += l[0];
    ans += l[1];
  }
  aux[0] -= (aux[1] - aux[2]);
  aux[1] = aux[2];
  for (int i = 0; i < (aux[0]); i++) {
    if (i & 1) {
      ans += l[0];
      ans += l[1];
      aux[1]--;
    } else {
      ans += l[0];
      ans += l[2];
      aux[2]--;
    }
  }
  if (aux[0] & 1) {
    ans += l[1];
    aux[1]--;
  }
  for (int i = 0; i < (aux[2]); i++) {
    ans += l[2];
    ans += l[1];
  }

  return (ans);
}

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int t, N;
  cin >> t;
  int R, O, Y, G, B, V;
  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> N;
    cin >> R >> O >> Y >> G >> B >> V;
    R -= G;
    Y -= V;
    B -= O;
    if (R == 0 and G) {
      if (N == 2 * G) {
        string ans = "";
        for (int i = 0; i < (N / 2); i++) {
          ans += "RG";
        }
        cout << "Case #" << caso << ": " << ans << endl;
      } else {
        cout << "Case #" << caso << ": "
             << "IMPOSSIBLE" << endl;
      }
      continue;
    }
    if (Y == 0 and V) {
      if (N == 2 * V) {
        string ans = "";
        for (int i = 0; i < (N / 2); i++) {
          ans += "YV";
        }
        cout << "Case #" << caso << ": " << ans << endl;
      } else {
        cout << "Case #" << caso << ": "
             << "IMPOSSIBLE" << endl;
      }
      continue;
    }
    if (B == 0 and O) {
      if (N == 2 * O) {
        string ans = "";
        for (int i = 0; i < (N / 2); i++) {
          ans += "BO";
        }
        cout << "Case #" << caso << ": " << ans << endl;
      } else {
        cout << "Case #" << caso << ": "
             << "IMPOSSIBLE" << endl;
      }
      continue;
    }

    // cout << R << " " << Y << " " << B << endl;
    string ans = solve(R, Y, B);
    string a = "";
    int l = ans.size();
    if (ans == "IMPOSSIBLE")
      a = ans;
    else {
      int o = 0;
      int g = 0;
      int v = 0;
      for (int i = 0; i < (l); i++) {
        a += ans[i];
        if (ans[i] == 'R' and g < G) {
          a += "GR";
          g++;
        }
        if (ans[i] == 'Y' and v < V) {
          a += "VY";
          v++;
        }
        if (ans[i] == 'B' and o < O) {
          a += "OB";
          o++;
        }
      }
    }

    cout << "Case #" << caso << ": " << a << endl;
  }

  return 0;
}
