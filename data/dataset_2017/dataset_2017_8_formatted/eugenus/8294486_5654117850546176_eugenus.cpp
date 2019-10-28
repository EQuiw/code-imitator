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

#define forn(i, n) for (int i = 0; i < (n); i++)
#define forsn(i, s, n) for (int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair

using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

string solve(int R, int Y, int B) {
  int aux[3];
  aux[0] = R;
  aux[1] = Y;
  aux[2] = B;
  forn(i, 3) {
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
  forn(i, aux[1] - aux[2]) {
    ans += l[0];
    ans += l[1];
  }
  aux[0] -= (aux[1] - aux[2]);
  aux[1] = aux[2];
  forn(i, aux[0]) {
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
  forn(i, aux[2]) {
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
  forsn(caso, 1, t + 1) {
    cin >> N;
    cin >> R >> O >> Y >> G >> B >> V;
    R -= G;
    Y -= V;
    B -= O;
    if (R == 0 and G) {
      if (N == 2 * G) {
        string ans = "";
        forn(i, N / 2) { ans += "RG"; }
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
        forn(i, N / 2) { ans += "YV"; }
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
        forn(i, N / 2) { ans += "BO"; }
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
      forn(i, l) {
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